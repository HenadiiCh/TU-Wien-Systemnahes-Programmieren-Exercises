#pragma once

#define iuenum_PI 3.14159265358979323846

#include <math.h>    // fabs, fmax
#include <stdbool.h> // bool, true, false

/// @brief Checks if two floating point values are close to each other
/// @param a First value
/// @param b Second value
/// @param tabs Tolerance for the absolute difference:
///        abs(a - b) < tabs
/// @param trel Tolerance for the relative error (using the larger absolute value as reference):
///        abs(a  b) < trel * max(abs(a),abs(b))
/// @return true if the weaker of the two tolerances is met, false otherwise
static bool iuenum_isclose_tol(double a, double b, double tabs, double trel) {
  if (a == b) // for infinite values (which should be considered close to themselves)
    return true;
  double abs_diff = fabs(a - b);            // absolte difference
  double trel_ref = fmax(fabs(a), fabs(b)); // reference for the relative threshold
  return abs_diff < fmax(tabs, trel * trel_ref);
}

/// @brief Checks if two floating point values are close to each other using a default tolerances
/// absolute tolerance: 0.0  i.e., there is no tolerance w.r.t the absolute value
/// relative tolerance: 1e-9 i.e., robust tolerance to an expected value (analytic value or alternative calculation)
/// @param a First value
/// @param b Second value
/// @return true if the two values are close (up to a robust difference resulting from finite-precision calculations)
static bool iuenum_isclose(double a, double b) {
  return iuenum_isclose_tol(a, b, 0.0, 1e-9);
}
