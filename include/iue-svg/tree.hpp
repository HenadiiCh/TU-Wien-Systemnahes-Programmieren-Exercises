/// @file
/// @brief Educational implementation of a tree data structure with value semantics
/// @note The implementation relies on the "minimal incomplete type support" incomplete type support for std::list
/// - https://en.cppreference.com/w/cpp/feature_test#cpp_lib_incomplete_container_elements

#pragma once

#include <cstddef>    // std::size_t
#include <functional> // std::function
#include <list>       // std::string

namespace iue::svg {

template <typename T>
concept Value = requires(const T& a, T& b) {
  T(a);  ///< copy constructor (std::copy_constructible)
  b = a; ///< copy assignment (std::assignable_from)
};

/// @brief Generic tree (tree with a dynamic unbound number of child nodes)
template <Value Value> struct Tree {

  /// @brief Node in the tree
  struct Node {
    Value value;                ///< Stored value
    std::list<Node> nodes = {}; ///< List of child nodes
  };

  using ValueVisitor = std::function<void(const Value& value, std::size_t level)>;
  using NodeVisitor = std::function<void(const Node& node, std::size_t level)>;

  Node org; ///<  Root node of the tree

  /// @brief Constructs a tree
  /// @param Value held by the root node of the tree
  /// @note This constructor avoids that the value type needs to be default-constructible
  Tree(const Value& value) : org{value} {}

  /// @brief Visit all values in the nodes in preorder using two visitors for down and up path
  static void preorder(Node& root, const ValueVisitor& down, const ValueVisitor& up, std::size_t level = 0) {
    down(root.value, level);
    for (auto& child : root.nodes)
      preorder(child, down, up, level + 1);
    up(root.value, level);
  }

  /// @brief Visit all nodes in preorder using two visitors for down and up path
  static void preorder(Node& root, const NodeVisitor& down, const NodeVisitor& up, std::size_t level = 0) {
    down(root, level);
    for (auto& child : root.nodes)
      preorder(child, down, up, level + 1);
    up(root, level);
  }
};

} // namespace iue::svg
