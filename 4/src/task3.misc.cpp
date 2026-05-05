/// @file
/// @brief Task3: definitions of helper functions for the implementation and tests

#include "task3.misc.hpp"

#include "task2.hpp" // task2::BBox, task2::Circle, task2::Triangle,

#include "iue-svg/render.hpp" // iue::svg::render

#include <algorithm>  // std::algorithm
#include <filesystem> // std::filesystem::path

namespace task3
{

    task2::BBox render_wrapper(std::filesystem::path filepath,
                               const std::vector<task2::BBox>& bboxes,
                               const std::vector<task2::Circle>& circles,
                               const std::vector<task2::Triangle>& triangles)
    {

        auto circle_convert = [](const task2::Circle& in) -> iue::svg::Circle { return {in.c, in.r}; };
        std::vector<iue::svg::Circle> c;
        std::transform(circles.begin(), circles.end(), std::back_inserter(c), circle_convert);

        auto triangle_convert = [](const task2::Triangle& in) -> iue::svg::Triangle { return {in.abc}; };
        std::vector<iue::svg::Triangle> t;
        std::transform(triangles.begin(), triangles.end(), std::back_inserter(t), triangle_convert);

        auto bbox_convert = [](const task2::BBox& in) -> iue::svg::BBox { return iue::svg::BBox{in.min, in.max}; };
        std::vector<iue::svg::BBox> r;
        std::transform(bboxes.begin(), bboxes.end(), std::back_inserter(r), bbox_convert);

        auto [bbmin, bbmax] = iue::svg::render(filepath, r, c, t);

        return {bbmin, bbmax};
    }

} // namespace task3