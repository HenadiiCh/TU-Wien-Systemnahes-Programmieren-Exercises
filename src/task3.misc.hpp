/// @file
/// @brief Task3: declaration of helper functions for the implementation

#pragma once

#include "task2.hpp" // task3::render_something

#include <filesystem> // std::filesystem::path
#include <vector>     // std::vector

namespace task3
{

    /// @brief Wrapper function for 'iue::svg::render' to support direct plotting of the types from task2:
    ///        task2::BBox,
    ///        task2::Circle
    ///        task2::Triangle
    /// @param filepath Filename of the produced SVG-Image
    /// @param bboxes Sequence of bounding boxes to be plotted
    /// @param circles Sequence of circles to be plotted
    /// @param triangles Sequence of triangles to be plotted
    /// @return Enclosing bounding box of all rendered primitives
    task2::BBox render_wrapper(std::filesystem::path filepath,
                               const std::vector<task2::BBox>& bboxes,
                               const std::vector<task2::Circle>& circles,
                               const std::vector<task2::Triangle>& triangles);

} // namespace task3
