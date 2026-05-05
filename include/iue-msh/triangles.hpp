/// @file
/// @brief Class definition and inline member functions for creating generic regular square triangle
/// meshes

#pragma once

#include "iue-svg/render.hpp" // iue::svg::render
#include "iue-svg/tags.hpp"   // iue::svg::Triangle

#include <algorithm>     // std::sort, std::ranges::max, std::max
#include <array>         // std::array
#include <cassert>       // assert
#include <filesystem>    // std::filesystem
#include <iostream>      // std::cout, std::endl
#include <limits>        // std::numeric_limits
#include <map>           // std::map
#include <set>           // std::set, std::multiset
#include <sstream>       // std::ostringstream
#include <string>        // std::string
#include <tuple>         // std::tuple
#include <unordered_set> // std::unordered_set
#include <utility>       // std::pair
#include <vector>        // std::vector, std::erase_if

/// @brief Class definition and member function declarations
namespace iue::msh {

///@brief Two-dimensional triangle mesh
class Triangles {

public:
  ///@brief Vertex coordinate
  using Vec2d = std::array<double, 2>;

  ///@brief Index triplet
  using Vec3i = std::array<size_t, 3>;

  ///@brief Axis-aligned bounding box described using the bottom left and upper right coordinate
  using BBox = std::tuple<Vec2d, Vec2d>;

private:
  std::vector<Vec2d> vertices;  ///< sequence of vertices
  std::vector<Vec3i> triangles; ///< sequence of index triplets each indexing the three corner
                                ///< vertices of a triangle

public:
  /// @brief Generates a regular triangular mesh pattern inside an axis-aligned bounding box
  /// @param box Axis-aligned bounding box of the generated mesh
  /// @param h Lower bound for the edge length of the generate triangles
  Triangles(BBox box, double h);

  /// @brief Calculates the current axis-aligned bounding box
  /// @return Bounding box of all triangles/vertices in the mesh
  BBox bbox() const;

  /// @brief Read-only access to the vertices of the mesh
  /// @return Reference to the underlying sequence of vertices
  const std::vector<Vec2d>& getVertices() const;

  /// @brief Read-only access to triangles of the mesh
  /// @return Reference to the underlying sequence of triangles
  const std::vector<Vec3i>& getTriangles() const;

  /// @brief Prints the sequences of vertices and triangles to a string;
  std::string str() const;

  /// @brief Generate SVG image
  /// @param filepath Filename for the generated output
  BBox save(std::filesystem::path filepath) const;

  /// @brief Evaluates the invariants of the class
  /// @return false, if any of the invariants is violated, true otherwise
  /// Invariants:
  ///   - each triangle references valid indices
  ///   - each triangle references three distinct corners
  ///   - edges are not occupied more than twice (no hidden edges)
  ///   - no unreferenced vertices are present
  bool check_invariants() const;

  /// @brief Removes a set of vertices from the mesh:
  ///   - all triangles connected to the removed vertices are removed
  ///   - all unused vertices potentially originating from the triangle removal are removed
  /// @param indices Vertex indices to be removed
  /// @return Total number of removed vertices and total number of removed triangles
  std::tuple<size_t, size_t> remove_vertices(std::unordered_set<size_t> indices);
};

} // namespace iue::msh

/// @brief Inline member function definitions
namespace iue::msh {

inline Triangles::Triangles(Triangles::BBox box, double h) : vertices(), triangles() {

  auto [min, max] = box;

  assert(max[0] > min[0]);
  assert(max[1] > min[1]);

  auto width = max[0] - min[0];
  auto height = max[1] - min[1];

  unsigned int nx = (width / h) + 1;
  unsigned int ny = (height / h) + 1;

  assert(nx >= 2);
  assert(ny >= 2);

  vertices.resize(nx * ny);

  for (auto iy = 0U; iy != ny; ++iy) {
    for (auto ix = 0U; ix != nx; ++ix) {
      vertices.at(ix + iy * nx) = {ix * h + min[0], iy * h + min[1]};
    }
  }

  triangles.reserve((nx - 1) * (ny - 1) * 2);
  for (auto iy = 1U; iy != ny; ++iy) {
    for (auto ix = 1U; ix != nx; ++ix) {
      auto i = ix + iy * nx;
      auto ia = i - nx - 1;
      auto ib = i - nx;
      auto ic = i;
      auto id = i - 1;
      triangles.push_back({ia, ib, id});
      triangles.push_back({ib, ic, id});
    }
  }
}

inline Triangles::BBox Triangles::bbox() const {
  Vec2d bbmin = {+std::numeric_limits<double>::max(), +std::numeric_limits<double>::max()};
  Vec2d bbmax = {-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max()};

  // update minmax from single coordinate
  auto minmax = [&bbmin, &bbmax](const Vec2d& p) {
    bbmin[0] = bbmin[0] < p[0] ? bbmin[0] : p[0];
    bbmin[1] = bbmin[1] < p[1] ? bbmin[1] : p[1];
    bbmax[0] = bbmax[0] > p[0] ? bbmax[0] : p[0];
    bbmax[1] = bbmax[1] > p[1] ? bbmax[1] : p[1];
  };

  for (const auto& v : vertices) {
    minmax(v);
  }

  return {bbmin, bbmax};
}

inline const std::vector<Triangles::Vec2d>& Triangles::getVertices() const { return vertices; }

inline const std::vector<Triangles::Vec3i>& Triangles::getTriangles() const { return triangles; }

inline std::string Triangles::str() const {
  auto stream = std::ostringstream{};
  std::cout << "Triangles [" << std::endl;
  std::cout << "  vertices [" << std::endl;
  { // print vertices
    size_t index = 0;
    for (const auto& [x, y] : vertices)
      stream << "    " << index++ << ": ( " << x << "," << y << " )" << std::endl;
    stream << "  ]" << std::endl;
  }
  { // print triangles
    size_t index = 0;
    stream << "  triangles [" << std::endl;
    for (const auto& [ia, ib, ic] : triangles)
      stream << "    " << index++ << ": ( " << ia << "," << ib << "," << ic << " )" << std::endl;
    stream << "  ]" << std::endl;
  }
  stream << "]" << std::endl;

  return stream.str();
}

inline Triangles::BBox Triangles::save(std::filesystem::path filepath) const {

  std::vector<iue::svg::Triangle> tris;

  for (const auto& [ia, ib, ic] : triangles) {
    tris.push_back({vertices[ia], vertices[ib], vertices[ic]});
  }

  return iue::svg::render(filepath, {}, {}, tris);
}

inline bool Triangles::check_invariants() const {

  std::set<size_t> vertices_in_use = {};
  std::multiset<std::pair<size_t, size_t>> edges;
  for (auto i3 : triangles) {
    std::sort(i3.begin(), i3.end());
    edges.insert({i3[0], i3[1]});
    edges.insert({i3[1], i3[2]});
    edges.insert({i3[2], i3[0]});

    // check: each triangle references three distinct corners
    if (std::set<size_t>{i3[0], i3[1], i3[2]}.size() != 3) {
      return false;
    }

    // check: each triangle references valid indices
    if (std::ranges::max(i3) >= vertices.size()) {
      return false;
    }

    vertices_in_use.insert(i3[0]);
    vertices_in_use.insert(i3[1]);
    vertices_in_use.insert(i3[2]);
  }

  // check: edges are not occupied more than twice (no hidden edges)
  for (const auto& edge : edges) {
    if (edges.count(edge) > 2) {
      return false;
    }
  }

  // check: no unreferenced vertices are present
  if (vertices_in_use.size() != vertices.size()) {
    return false;
  }

  return true;
}

inline std::tuple<size_t, size_t> Triangles::remove_vertices(std::unordered_set<size_t> indices) {

  if (indices.empty())
    return {0, 0};

  assert(indices.size() != 0);
  assert(std::ranges::max(indices) <= vertices.size());

  // remove connected triangles
  auto connected = [&indices](const Vec3i& triangle) -> bool {
    const auto& [ia, ib, ic] = triangle;
    return indices.contains(ia) || indices.contains(ib) || indices.contains(ic);
  };
  auto num_removed_triangles = std::erase_if(triangles, connected);

  // find additional points which became unused (due to removal of triangles) and ...
  std::unordered_set<size_t> in_use;
  for (auto& [ia, ib, ic] : triangles) {
    in_use.insert(ia);
    in_use.insert(ib);
    in_use.insert(ic);
  }
  // .. add those to the list of indices to be removed
  for (size_t i = 0; i != vertices.size(); ++i) {
    if (in_use.find(i) == in_use.end()) {
      indices.insert(i);
    }
  }

  // remove vertices and record offsets
  std::map<size_t, ptrdiff_t> offsets;
  ptrdiff_t offset = 0;
  size_t index = 0;
  auto remove = [&index, &indices, &offsets, &offset](const Vec2d&) -> bool {
    if (indices.contains(index)) {
      std::pair<size_t, ptrdiff_t> pair = {std::max<ptrdiff_t>(index - 1, 0), offset--};
      offsets.insert(pair);
      ++index;
      return true;
    }
    ++index;
    return false;
  };
  auto num_removed_vertices = std::erase_if(vertices, remove);

  // add final offset
  std::pair<size_t, ptrdiff_t> pair = {std::max<ptrdiff_t>(index - 1, 0), offset};
  offsets.insert(pair);

  // update triangle indices using recorded offsets
  for (auto& triangle : triangles) {
    for (auto& i : triangle) {
      auto iter = offsets.lower_bound(i);
      if (iter != offsets.end())
        i += iter->second;
    }
  }

  return {num_removed_vertices, num_removed_triangles};
}

} // namespace iue::msh