/// @file
/// @brief Task2: member function definitions/implementations

#include "task2.hpp"      // task2::Vec2, task2::BBox, task2::Circle, task2::Triangle
#include "task2.misc.hpp" // task2::operator<<, task2::isnan, task2::isclose

#include "iue-num/numerics.hpp" // iue::num::isclose

/// @todo Include standard library headers as needed
#include <cmath>     // std::sin, std::cos, std::abs
#include <algorithm> // std::min, std::max

namespace task2
{

    /// ====================================  Bounding Box =================================================
    /// @todo Implement the missing member functions for bounding box as declared and specified in task2.hpp

    /// @todo implement member function 'BBox::scale'
    BBox BBox::scale(const Vec2d& org, double s) const
    {
        // Scale min and max relative to the origin (Skalierung von min und max relativ zum Ursprung)
        Vec2d new_min = {org[0] + (min[0] - org[0]) * s, org[1] + (min[1] - org[1]) * s};
        Vec2d new_max = {org[0] + (max[0] - org[0]) * s, org[1] + (max[1] - org[1]) * s};
        
        // Ensure min is still smaller than max (Sicherstellen, dass min <= max ist)
        return {
            {std::min(new_min[0], new_max[0]), std::min(new_min[1], new_max[1])},
            {std::max(new_min[0], new_max[0]), std::max(new_min[1], new_max[1])}
        };
    }

    /// @todo implement member function 'BBox::translate'
    BBox BBox::translate(const Vec2d& offset) const
    {
        // Translate by offset (Verschieben um den Offset)
        return {{min[0] + offset[0], min[1] + offset[1]}, {max[0] + offset[0], max[1] + offset[1]}};
    }

    /// @todo implement member function 'BBox::check_invariants'
    bool BBox::check_invariants() const
    {
        // Check for NAN (Prüfen auf NAN)
        if (task2::isnan(min) || task2::isnan(max)) {
            return false;
        }
        // Check if min is less or equal to max (Min muss <= Max sein)
        if (min[0] > max[0] || min[1] > max[1]) {
            return false;
        }
        // Check if min is close to max (Min darf nicht nah an Max sein)
        if (iue::num::isclose(min[0], max[0]) && iue::num::isclose(min[1], max[1])) {
            return false;
        }
        return true;
    }

    /// ====================================  Circle  ================================================
    /// @todo Implement the missing member functions for Circle as declared and specified in task2.hpp

    /// @todo implement member function 'Circle::bbox'
    BBox Circle::bbox() const
    {
        // Bounding box for a circle (Bounding Box für einen Kreis berechnen)
        return {{c[0] - r, c[1] - r}, {c[0] + r, c[1] + r}};
    }

    /// @todo implement member function 'Circle::scale'
    Circle Circle::scale(const Vec2d& org, double s) const
    {
        // Scale center and radius (Mittelpunkt und Radius skalieren)
        Vec2d new_c = {org[0] + (c[0] - org[0]) * s, org[1] + (c[1] - org[1]) * s};
        double new_r = r * std::abs(s);
        return {new_c, new_r};
    }

    /// @todo implement member function 'Circle::rotate'
    Circle Circle::rotate(const Vec2d& org, double angle) const
    {
        // Rotate center around org (Mittelpunkt um den Ursprung rotieren)
        double dx = c[0] - org[0];
        double dy = c[1] - org[1];
        double new_x = org[0] + (dx * std::cos(angle) - dy * std::sin(angle));
        double new_y = org[1] + (dx * std::sin(angle) + dy * std::cos(angle));
        return {{new_x, new_y}, r};
    }

    /// @todo implement member function 'Circle::translate'
    Circle Circle::translate(const Vec2d& offset) const
    {
        // Translate center (Verschieben des Mittelpunktes)
        return {{c[0] + offset[0], c[1] + offset[1]}, r};
    }

    /// @todo implement member function 'Circle::check_invariants'
    bool Circle::check_invariants() const
    {
        // Check invariants: radius non-negative and no NANs (Radius >= 0 und keine NANs)
        if (r < 0.0 || std::isnan(r) || task2::isnan(c)) {
            return false;
        }
        return true;
    }

    /// ====================================  Triangle  ================================================
    /// @todo Implement the missing member functions for Triangle as declared and specified in task2.hpp

    /// @todo implement member function 'Triangle::bbox'
    BBox Triangle::bbox() const
    {
        // Minimal axis-aligned bounding box (Minimale Bounding Box berechnen)
        double min_x = std::min({abc[0][0], abc[1][0], abc[2][0]});
        double min_y = std::min({abc[0][1], abc[1][1], abc[2][1]});
        double max_x = std::max({abc[0][0], abc[1][0], abc[2][0]});
        double max_y = std::max({abc[0][1], abc[1][1], abc[2][1]});
        return {{min_x, min_y}, {max_x, max_y}};
    }

    /// @todo implement member function 'Triangle::scale'
    Triangle Triangle::scale(const Vec2d& org, double s) const
    {
        // Scale each point relative to org (Jeden Punkt relativ zum Ursprung skalieren)
        Triangle res = *this;
        for (int i = 0; i < 3; ++i) {
            res.abc[i][0] = org[0] + (abc[i][0] - org[0]) * s;
            res.abc[i][1] = org[1] + (abc[i][1] - org[1]) * s;
        }
        return res;
    }

    /// @todo implement member function 'Triangle::rotate'
    Triangle Triangle::rotate(const Vec2d& org, double angle) const
    {
        // Rotate each point around org (Jeden Punkt um den Ursprung rotieren)
        Triangle res = *this;
        for (int i = 0; i < 3; ++i) {
            double dx = abc[i][0] - org[0];
            double dy = abc[i][1] - org[1];
            res.abc[i][0] = org[0] + (dx * std::cos(angle) - dy * std::sin(angle));
            res.abc[i][1] = org[1] + (dx * std::sin(angle) + dy * std::cos(angle));
        }
        return res;
    }

    /// @todo implement member function 'Triangle::translate'
    Triangle Triangle::translate(const Vec2d& offset) const
    {
        // Translate each point (Jeden Punkt verschieben)
        Triangle res = *this;
        for (int i = 0; i < 3; ++i) {
            res.abc[i][0] += offset[0];
            res.abc[i][1] += offset[1];
        }
        return res;
    }

    /// @todo implement member function 'Triangle::check_invariants'
    bool Triangle::check_invariants() const
    {
        // Check for NAN and closeness of corners (Prüfen auf NAN und ob die Ecken nah beieinander liegen)
        for (int i = 0; i < 3; ++i) {
            if (task2::isnan(abc[i])) return false;
        }
        
        bool c01 = iue::num::isclose(abc[0][0], abc[1][0]) && iue::num::isclose(abc[0][1], abc[1][1]);
        bool c12 = iue::num::isclose(abc[1][0], abc[2][0]) && iue::num::isclose(abc[1][1], abc[2][1]);
        bool c20 = iue::num::isclose(abc[2][0], abc[0][0]) && iue::num::isclose(abc[2][1], abc[0][1]);
        
        // Triangle invariant: none of the corners are close to each other
        if (c01 || c12 || c20) {
            return false;
        }
        return true;
    }

} // namespace task2
