/// @file
/// @brief Test for 'iue::svg::render'

#include "iue-svg/render.hpp"   // iue::svg::render
#include "iue-num/numerics.hpp" // iue::num::isclose
#include "iue-svg/tags.hpp"     // iue::svg::Circle, iue::svg::Triangle, iue::svg::BBox

int main() {

  std::vector<iue::svg::Circle> circles;
  circles.push_back(iue::svg::Circle{{1, 1}, 1});
  circles.push_back(iue::svg::Circle{{2, 2}, 2});
  circles.push_back(iue::svg::Circle{{3, 3}, 3});
  circles.push_back(iue::svg::Circle{{10, 10}, 10});

  std::vector<iue::svg::Triangle> triangles;
  triangles.push_back(iue::svg::Triangle{{{50, 50}, {49, 50}, {50, 49}}});
  triangles.push_back(iue::svg::Triangle{{{50, 50}, {48, 50}, {50, 48}}});
  triangles.push_back(iue::svg::Triangle{{{50, 50}, {47, 50}, {50, 47}}});
  triangles.push_back(iue::svg::Triangle{{{50, 50}, {40, 50}, {50, 40}}});

  std::vector<iue::svg::BBox> bboxes;
  bboxes.push_back(iue::svg::BBox{{0, 49}, {1, 50}});
  bboxes.push_back(iue::svg::BBox{{0, 48}, {2, 50}});
  bboxes.push_back(iue::svg::BBox{{0, 47}, {4, 50}});
  bboxes.push_back(iue::svg::BBox{{0, 40}, {10, 50}});

  auto [bbmin, bbmax] = iue::svg::render("render.test.svg", bboxes, circles, triangles);

  assert(iue::num::isclose(bbmin[0], 0));
  assert(iue::num::isclose(bbmin[1], 0));

  assert(iue::num::isclose(bbmax[0], 50));
  assert(iue::num::isclose(bbmax[1], 50));  

  return 0;
}
