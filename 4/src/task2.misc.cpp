/// @file
/// @brief Task2: definitions of helper functions for the implementation and tests

#include "task2.misc.hpp"
#include "task2.hpp" // task2::Vec2, task2::BBox, task2::Circle, task2::Triangle

#include "iue-num/numerics.hpp" // iue::num::isclose

#include <algorithm> // std::ranges::sort, std::ranges::next_permutation
#include <array>     // std::array
#include <iostream>  // std::ostream,  std::endl

namespace task2
{

    std::ostream& operator<<(std::ostream& os, const task2::Vec2d& v)
    {
        return os << "( " << v[0] << ", " << v[1] << " )";
    }

    std::ostream& operator<<(std::ostream& os, const task2::BBox& v)
    {
        return os << "BBox [ " << std::endl
                  << "  min = " << v.min << std::endl
                  << "  max = " << v.max << std::endl
                  << "]";
    }

    std::ostream& operator<<(std::ostream& os, const task2::Circle& v)
    {
        return os << "Circle [ " << std::endl
                  << "  center = " << v.c << std::endl
                  << "  radius = " << v.r << std::endl
                  << "]";
    }

    std::ostream& operator<<(std::ostream& os, const task2::Triangle& v)
    {
        return os << "Triangle [ " << std::endl
                  << "  a = " << v.abc[0] << std::endl
                  << "  b = " << v.abc[1] << std::endl
                  << "  c = " << v.abc[2] << std::endl
                  << "]";
    }

    bool isclose(const task2::Vec2d& a, const task2::Vec2d& b)
    {
        if (!iue::num::isclose(a[0], b[0]))
            return false;
        if (!iue::num::isclose(a[1], b[1]))
            return false;
        return true;
    }

    bool isclose(const task2::BBox& a, const task2::BBox& b)
    {
        if (!isclose(a.min, b.min))
            return false;
        if (!isclose(a.max, b.max))
            return false;
        return true;
    }

    bool isclose(const task2::Circle& a, const task2::Circle& b)
    {
        if (!isclose(a.c, b.c))
            return false;
        if (!iue::num::isclose(a.r, b.r))
            return false;
        return true;
    }

    bool isclose(const task2::Triangle& a, const task2::Triangle& b)
    {
        for (int n = 0; n != 3; ++n)
            if (!isclose(a.abc[n], b.abc[n]))
                return false;
        return true;
    }

    bool isclose_permute(const task2::Triangle& a, const task2::Triangle& b)
    {
        auto permute = a.abc;
        std::sort(permute.begin(), permute.end()); // std::ranges::sort(permute);
        auto keep = b.abc;
        do
        {
            if (isclose({permute}, {keep}))
                return true;
        } while (
            std::next_permutation(permute.begin(), permute.end())); // std::ranges::next_permutation(permute).found)
        return false;
    }

    bool isnan(const Vec2d& v)
    {
        if (std::isnan(v[0]))
            return true;
        if (std::isnan(v[1]))
            return true;
        return false;
    }

} // namespace task2
