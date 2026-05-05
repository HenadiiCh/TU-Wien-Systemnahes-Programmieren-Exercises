/// @file
/// @brief Implementation of SVG-Tags for the SVG-writer in render.hpp

#pragma once

#include <array>         // std::array
#include <sstream>       // std::stringstream
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace iue::svg {

/// @brief convenience aliases for short notations
using Vec2d = std::array<double, 2>;
using Circle = std::tuple<Vec2d, double>;
using Polygon = std::vector<Vec2d>;
using Triangle = std::array<Vec2d, 3>;
using BBox = std::tuple<Vec2d, Vec2d>;
using Text = std::tuple<Vec2d, std::string>;

/// @brief Map for storing an open set of attribute/value pairs
using Attributes = std::unordered_map<std::string, std::string>;

/// @brief Requirements towards an XMLTag
template <typename T>
concept Tag = requires(const T& t) {
  { t.open() } -> std::same_as<std::string>;
  { t.text() } -> std::same_as<std::string>;
  { t.close() } -> std::same_as<std::string>;
};

/// @brief Implementation of an SVG XML-tag
struct XMLTag {
  std::string name;
  Attributes attributes;
  std::string content;
  bool self_closing;
  std::string text() const { return this->content; }
  std::string open() const {
    std::stringstream res;
    res << "<" << name;
    for (auto const& [key, val] : attributes)
      res << " " << key << "='" << val << "'";
    if (self_closing)
      res << "/>";
    else
      res << ">";
    return res.str();
  }
  std::string close() const {
    std::stringstream res;
    if (!self_closing)
      res << "</" << name << ">";
    return res.str();
  }
};

/// @brief Check if Tag requirements are fullfilled
static_assert(Tag<XMLTag>);

/// @brief Root SVG Element
/// <svg preserveAspectRatio='xMidYMid meet' viewbox='0 0 w h' height='w' width='h'></svg>
inline XMLTag svg(const Vec2d& bbmin, const Vec2d& bbmax) {
  Attributes attributes;
  // add data attributes
  auto const& [xmin, ymin] = bbmin;
  auto const& [xmax, ymax] = bbmax;
  double width = std::abs(xmax - xmin);
  double height = std::abs(ymax - ymin);
  attributes.insert({"width", std::to_string(width)});
  attributes.insert({"height", std::to_string(height)});
  std::stringstream viewbox;
  for (const auto& val : {xmin, ymin, width, height})
    viewbox << val << " ";
  attributes.insert({"viewbox", viewbox.str()});
  // add default attributes
  attributes.insert({"xmlns", "http://www.w3.org/2000/svg"});
  attributes.insert({"version", "1.1"});
  attributes.insert({"preserveAspectRatio", "xMidYMid meet"});
  // final assembly
  return {"svg", attributes, std::string{}, false};
}

/// @brief Group SVG Element
/// <g></g>
inline XMLTag group(const Attributes& custom_attributes = {}) {
  Attributes attributes;
  // add custom attributes
  attributes.insert(custom_attributes.begin(), custom_attributes.end());
  // final assembly
  return {"g", attributes, std::string{}, false};
}

/// @brief Circle SVG Element
/// <circle r='r0' cx='cx' cy='cy' stroke-width='1' fill='none' stroke='black'/>
inline XMLTag circle(const Circle& circle, const Attributes& custom_attributes = {}) {
  Attributes attributes;
  // add data attributes
  const auto& [center, radius] = circle;
  const auto& [cx, cy] = center;
  attributes.insert({"cx", std::to_string(cx)});
  attributes.insert({"cy", std::to_string(cy)});
  attributes.insert({"r", std::to_string(radius)});
  // add custom attributes
  attributes.insert(custom_attributes.begin(), custom_attributes.end());
  // add default attributes
  attributes.insert({"stroke-width", std::to_string(1)});
  attributes.insert({"stroke", "black"});
  attributes.insert({"fill", "none"});
  // final assembly
  return {"circle", attributes, std::string{}, true};
}

/// @brief Polygon SVG Element
/// <polygon fill='none' stroke='black' stroke-width='1' points=' x1,y1 x2,y2, x3,y3 ... '/>
inline XMLTag polygon(const Polygon& polygon, const Attributes& custom_attributes = {}) {
  Attributes attributes;
  // add data attributes
  std::stringstream points;
  for (const auto& [x, y] : polygon)
    points << x << "," << y << " ";
  attributes.insert({"points", points.str()});
  // add custom attributes
  attributes.insert(custom_attributes.begin(), custom_attributes.end());
  // add default attributes
  attributes.insert({"stroke-width", std::to_string(1)});
  attributes.insert({"stroke", "black"});
  attributes.insert({"fill", "none"});
  // final assembly
  return {"polygon", attributes, std::string{}, true};
}

/// @brief Text SVG Element
/// <text font-size='10' text-anchor='middle' x='x' y='y' > content </text>
inline XMLTag text(const Text& text, const Attributes& custom_attributes = {}) {
  Attributes attributes;
  // add data attributes
  const auto& [anchor, content] = text;
  const auto& [x, y] = anchor;
  attributes.insert({"x", std::to_string(x)});
  attributes.insert({"y", std::to_string(y)});
  // add custom attributes
  attributes.insert(custom_attributes.begin(), custom_attributes.end());
  // add default attributes
  attributes.insert({"font-size", std::to_string(10)});
  attributes.insert({"text-anchor", "middle"}); 
  return {"text", attributes, content, false};
}

} // namespace iue::svg
