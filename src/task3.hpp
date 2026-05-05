/// @file
/// @brief Task3: function declarations

#pragma once

#include <filesystem> // std::filesystem::path

namespace task3
{

    /// @brief Renders an SVG image
    /// @param filepath Filename of the produced SVG-Image
    /// @return Total number of geometric primitives (Bbox, Circle, Triangle) plotted
    /// @note the content of the image is not restricted, but you need to plot at least 200 primitives
    int render_something(std::filesystem::path filepath);

} // namespace task3
