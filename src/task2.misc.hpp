/// @file
/// @brief Task2: declaration of helper functions for the implementation and tests

#pragma once

#include "task2.hpp" // task2::Vec2d, task2::BBox, task2::Circle, task2::Triangle

#include <iostream> // std::ostream

namespace task2
{

    /// @brief helper functions to print to the console
    std::ostream& operator<<(std::ostream& os, const task2::Vec2d& v);
    std::ostream& operator<<(std::ostream& os, const task2::BBox& v);
    std::ostream& operator<<(std::ostream& os, const task2::Circle& v);
    std::ostream& operator<<(std::ostream& os, const task2::Triangle& v);

    /// @brief helper function checking if a NAN is present
    bool isnan(const Vec2d& v);

    /// @brief helper functions for checking if two objects are numerically close
    bool isclose(const task2::Vec2d& a, const task2::Vec2d& b);
    bool isclose(const task2::BBox& a, const task2::BBox& b);
    bool isclose(const task2::Circle& a, const task2::Circle& b);
    bool isclose(const task2::Triangle& a, const task2::Triangle& b);

    /// @brief helper function comparing Triangles including permutations of corners
    bool isclose_permute(const task2::Triangle& a, const task2::Triangle& b);

} // namespace task2
