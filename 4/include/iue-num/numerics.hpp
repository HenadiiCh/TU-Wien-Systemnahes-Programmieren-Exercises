/// @file
/// @brief Supporting functionality for numeric calculations with floating point values

#pragma once

#include <cmath> // std::abs, std::max, std::min

namespace iue::num {

/// @brief Checks if two floating point values are close to each other
/// @param a First value
/// @param b Second value
/// @param tabs Tolerance for the absolute difference:
///        abs(a - b) < tabs
/// @param trel Tolerance for the relative error (using the larger absolute value as reference):
///        abs(a  b) < trel * max(abs(a),abs(b))
/// @return true if the stronger of the two tolerances is met, false otherwise
inline bool isclose(double a, double b, double tabs = 0.0, double trel = 1e-9) {
  if (a == b) // for infinite values (which should be considered close to themselves)
    return true;
  auto abs_diff = std::abs(a - b);                    // absolte difference
  auto trel_ref = std::max(std::abs(a), std::abs(b)); // reference for the relative threshold
  return abs_diff < std::max(tabs, trel * trel_ref);
}

} // namespace iue::num
