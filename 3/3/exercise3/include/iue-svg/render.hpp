/// @file
/// @brief Educational implementation of a SVG-Writer

#pragma once

#include "iue-svg/tags.hpp" // iue::svg:::XMLTag, iue::svg::svg
#include "iue-svg/tree.hpp" // iue::svg::Tree

#include <cassert>    // assert
#include <filesystem> // std::filesystem::path
#include <fstream>    // std::ofstream
#include <sstream>    // std::stringstream
#include <string>     // std::string
#include <vector>     // std::vector

namespace iue::svg {

/// @brief Generate a SVG file from sequences of compatible primitives
/// @return Enclosing bounding box (original unscaled coordinates)
/// Imporant notes:
/// 1. The outline of the svg will be the bounding box enclosing all occuring geometric primitives (based on coordinate)
///    - the detail of the extend of an object (textlength, fontsize, linewidth, ...) is **not** considered
/// 2. The coordinates are **scaled/rotated/translated before serializing**
///    - this is not so nice, but a scaling is required to improve the viewing experience for small coordinate spans
/// 3. All primitives are rendered with black lines and no fill
///    - the linewidth is choosen relative the the dimension of the enclosing bounding box
///    - the font-size for text is relative to the linewith
inline iue::svg::BBox render(std::filesystem::path filepath, const std::vector<iue::svg::BBox>& bboxes,
                   const std::vector<iue::svg::Circle>& circles, const std::vector<iue::svg::Triangle>& triangles) {

  using XMLTree = Tree<XMLTag>;

  assert(bboxes.size() != 0 || circles.size() != 0 || triangles.size() != 0);

  // calculate maximum extends
  Vec2d bbmin = {+std::numeric_limits<double>::max(), +std::numeric_limits<double>::max()};
  Vec2d bbmax = {-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max()};

  // update minmax from single coordinate
  auto minmax = [&bbmin, &bbmax](const Vec2d& p) {
    bbmin[0] = bbmin[0] < p[0] ? bbmin[0] : p[0];
    bbmin[1] = bbmin[1] < p[1] ? bbmin[1] : p[1];
    bbmax[0] = bbmax[0] > p[0] ? bbmax[0] : p[0];
    bbmax[1] = bbmax[1] > p[1] ? bbmax[1] : p[1];
  };

  for (const auto& circle : circles) {
    const auto& [c, r] = circle;
    minmax({c[0] - r, c[1] - r});
    minmax({c[0] + r, c[1] + r});
  }

  for (const auto& bbox : bboxes) {
    const auto& [min, max] = bbox;
    minmax(min);
    minmax(max);
  }

  for (const auto& triangle : triangles) {
    for (const auto& p : triangle)
      minmax(p);
  }

  // scaling
  double resolution;
  {
    auto const& [xmin, ymin] = bbmin;
    auto const& [xmax, ymax] = bbmax;
    double width = std::abs(xmax - xmin);
    double height = std::abs(ymax - ymin);
    resolution = std::max(width, height);
  }
  double unit = resolution / 800; // stroke referens is "thin" for a reference resolution
  double scale = 1 / unit;

  // scaling to have a unit stroke of 1
  auto sc = [scale](const Vec2d& p) -> Vec2d { return {p[0] * scale, p[1] * scale}; };
  auto scd = [scale](const double& val) -> double { return val * scale; };

  // transform to have bottom left origin (svg default is top left origin)
  auto tf = [xmin = bbmin[0], ymax = bbmax[1]](const Vec2d& p) -> Vec2d { return {(p[0] - xmin), (-p[1] + ymax)}; };

  // create tree with svg
  XMLTree dom{svg(sc(bbmin), sc(bbmax))};
  dom.org.nodes.push_back({svg::group()});
  auto& g = dom.org.nodes.back();

  { // plot all triangles
    for (const auto& triangle : triangles) {
      const auto& [a, b, c] = triangle;
      g.nodes.push_back({svg::polygon({sc(tf(a)), sc(tf(b)), sc(tf(c))})});
    }
  }

  { // plot all BBoxes
    for (const auto& bbox : bboxes) {
      const auto& [min, max] = bbox;
      const auto& [xmin, ymin] = min;
      const auto& [xmax, ymax] = max;
      std::vector<Vec2d> coords;
      coords.push_back(sc(tf({xmin, ymin})));
      coords.push_back(sc(tf({xmax, ymin})));
      coords.push_back(sc(tf({xmax, ymax})));
      coords.push_back(sc(tf({xmin, ymax})));
      g.nodes.push_back({svg::polygon(coords)});
    }
  }

  { // plot all circles
    for (const auto& circle : circles) {
      const auto& [c, r] = circle;
      g.nodes.push_back({svg::circle({sc(tf(c)), scd(r)})});
    }
  }

  { // plot bounding box of viewport
    const auto& [xmin, ymin] = bbmin;
    const auto& [xmax, ymax] = bbmax;
    std::vector<Vec2d> limits;
    limits.push_back(sc(tf({xmin, ymin})));
    limits.push_back(sc(tf({xmax, ymin})));
    limits.push_back(sc(tf({xmax, ymax})));
    limits.push_back(sc(tf({xmin, ymax})));
    g.nodes.push_back({svg::polygon(limits)});
  }

  // serialize tree to string
  std::stringstream stream;
  {

    auto down = [&stream](const XMLTag& value, std::size_t level) -> void {
      stream << std::string(2 * level, ' ') << value.open() << std::endl;
      auto text = value.text();
      if (!text.empty())
        stream << std::string(2 * level, ' ') << value.text() << std::endl;
    };

    auto up = [&stream](const XMLTag& value, std::size_t level) -> void {
      auto close = value.close();
      if (!close.empty())
        stream << std::string(2 * level, ' ') << value.close() << std::endl;
    };

    XMLTree::preorder(dom.org, down, up);
  }

  // save as file
  std::ofstream fs;
  fs.exceptions(std::ifstream::badbit);
  fs.open(filepath);
  fs << stream.str();

  return {bbmin, bbmax};
}

} // namespace iue::svg
