/// @file
/// @brief Task2: class definitions with member function declarations

#pragma once

#include <array> // std::array

namespace task2
{

    using Vec2d = std::array<double, 2>;

    /// @brief Axis-aligned bounding box
    struct BBox
    {

        Vec2d min; ///< coord of bottom left corner
        Vec2d max; ///< coord of top right corner

        /// @brief Scales the bounding box (relative to a reference coordinate)
        /// @param org Reference coordinate
        /// @param s Scaling factor
        BBox scale(const Vec2d& org, double s) const;
        /// @brief Translates the bounding box
        /// @param offset Translation vector
        BBox translate(const Vec2d& offset) const;
        /// @brief Checks if all invariants are fullfilled
        /// @return false if any invariant is violated, true otherwise
        /// Invariants:
        ///   - no coordinate is NAN
        ///   - the individual coordinates of 'min' are less or equal the respective coordinates in 'max'
        ///   - 'min' is not close to 'max' (use iue::num::isclose to check)
        bool check_invariants() const;
    };

    /// @brief Circle
    struct Circle
    {

        Vec2d c;  ///< coordinate of the center of the circle
        double r; ///< radius of the circle

        /// @brief Generates the minimum axis-aligned bounding box containing this circle
        /// @return axis-aligned bounding box
        BBox bbox() const;
        /// @brief Scales the circle center (relative to a reference coordinate), and the radius with a scalar value
        /// @param org Reference coordinate
        /// @param s Scaling factor
        Circle scale(const Vec2d& org, double s) const;
        /// @brief Rotates the circle center (relative to a reference coordinate) counter clockwise
        /// @param org Reference coordinate
        /// @param angle Rotation angle (in radians)
        Circle rotate(const Vec2d& org, double angle) const;
        /// @brief Translates the circle center
        /// @param offset Translation vector
        Circle translate(const Vec2d& offset) const;
        /// @brief Checks if all invariants are fullfilled
        /// @return false if any invariant is violated, true otherwise
        /// @note Invariants: radius is non-negative and no coordinate is NAN
        bool check_invariants() const;
    };

    /// @brief Triangle
    struct Triangle
    {

        std::array<Vec2d, 3> abc; ///< three corner points of the triangle

        /// @brief Generates the minimum axis-aligned bounding box containing this triangle
        /// @return axis-aligned bounding box
        BBox bbox() const;
        /// @brief Scales the triangle (relative to a reference coordinate)
        /// @param org Reference coordinate
        /// @param s Scaling factor
        Triangle scale(const Vec2d& org, double s) const;
        /// @brief Rotates the triangle (relative to a reference coordinate) counter clockwise
        /// @param org Reference coordinate
        /// @param angle Rotation angle (in radians)
        Triangle rotate(const Vec2d& org, double angle) const;
        /// @brief Translates the line
        /// @param offset Translation vector
        Triangle translate(const Vec2d& offset) const;
        /// @brief Checks if all invariants are fullfilled
        /// @return false if any invariant is violated, true otherwise
        /// Invariants:
        ///   - no coordinate is NAN
        ///   - none of the corner points are close to each other (use iue::num::isclose to check)
        bool check_invariants() const;
    };

} // namespace task2
