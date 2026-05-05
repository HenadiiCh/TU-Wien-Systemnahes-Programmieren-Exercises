/// @file
/// @brief Task3: function declarations

#pragma once

#include <tuple>  // std::tuple

/// @brief Calculates the real solutions of the quadratic equation a*x^2 + b*x + c = 0.
/// @param a coefficient (assume: 'a' is a non-zero value)
/// @param b coefficient
/// @param c coefficient
/// @return The two real solutions (order: ascending).
///         If no real solutions exists, the tuple contains two quiet NaNs.
std::tuple<double, double> solve_quadratic_equation(double a, double b, double c);

/// @brief Calculates the real solutions of the quadratic equation a*x^2 + b*x + c = 0.
/// @param abc coefficients (assume: the first element 'a' is a non-zero value)
/// @return The two real solutions (order: ascending).
///         If no real solutions exists, the tuple contains two quiet NaNs.
std::tuple<double, double> solve_quadratic_equation(std::tuple<double, double, double> abc);
