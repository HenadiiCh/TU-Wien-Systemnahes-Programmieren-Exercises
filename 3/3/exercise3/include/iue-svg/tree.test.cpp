/// @file
/// @brief Test for iue::svg::Tree 

#include "iue-svg/tree.hpp" // iue::svg::Tree

#include <cassert>  // assert
#include <cstddef>  // std::size_t
#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cout, std::endl
#include <sstream>  // std::stringstream
#include <string>   // std::string

struct Value {
  int a = 1;
};

int main() {

  using Tree = iue::svg::Tree<Value>;
  using Node = Tree::Node;

  Tree tree = {Value{0}};

  auto& l0 = tree.org;

  l0.nodes.push_back(Node{Value{1}});
  l0.nodes.push_back(Node{Value{1}});
  l0.nodes.push_back(Node{Value{1}});

  for (auto& l1 : l0.nodes) {
    l1.nodes.push_back(Node{Value{2}});
    l1.nodes.push_back(Node{Value{2}});
    l1.nodes.push_back(Node{Value{2}});
    for (auto& l1 : l1.nodes) {
      l1.nodes.push_back(Node{Value{3}});
      l1.nodes.push_back(Node{Value{3}});
    }
  }

  auto noop = [](const Value& value, std::size_t level) -> void {};

  { // print tree
    std::stringstream stream;

    auto print = [&stream](const Value& value, std::size_t level) -> void {
      stream << std::string(2 * level, ' ') << value.a << std::endl;
    };
    tree.preorder(l0, print, noop);
    std::cout << stream.str() << std::endl;
  }

  { // sum values in tree
    int sum = 0;
    auto count = [&sum](const Value& value, std::size_t level) -> void { sum += value.a; };
    tree.preorder(l0, count, noop);
    assert(sum == 1 * 0 + (1 * 3 * 1) + (1 * 3 * 3 * 2) + (1 * 3 * 3 * 2 * 3));
  }

  return EXIT_SUCCESS;
}