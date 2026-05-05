/// @file
/// @brief Test for iue::msg::Triangles

#include "iue-msh/triangles.hpp" // iue::msg::Triangles
#include "iue-num/numerics.hpp" // iue::num::isclose

#include <cassert>  // assert
#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cout, std::endl

int main() {

  using namespace iue::msh;

  auto min = Triangles::Vec2d{0.0, 0.0};
  auto max = Triangles::Vec2d{2.0, 1.0};
  auto h = 0.5;
  auto mesh = Triangles({min, max}, h);

  {
    assert(mesh.check_invariants());
    std::cout << mesh.str() << std::endl;
    auto [min, max] = mesh.save("triangles.test1.svg");
    assert(iue::num::isclose(min[1], 0));
  }

  mesh.remove_vertices({1, 2, 3, 4});

  {
    assert(mesh.check_invariants());
    std::cout << mesh.str() << std::endl;
    auto [min, max] = mesh.save("triangles.test2.svg");
    assert(iue::num::isclose(min[1],0.5));    
  }

  return EXIT_SUCCESS;
}