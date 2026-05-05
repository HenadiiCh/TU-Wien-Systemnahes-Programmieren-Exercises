/// @file
/// @brief Test for iue::num::islcose

#include "iue-num/numerics.hpp" // iue::num::islcose

#include <cassert> // assert
#include <cstdlib> // EXIT_SUCCESS
#include <limits>  // std::numeric_limits

int main() {

  const double eps = std::numeric_limits<double>::epsilon();
  const double inf = std::numeric_limits<double>::infinity();
  const double nan = std::numeric_limits<double>::quiet_NaN();

  { // infinity

    assert(iue::num::isclose(inf, inf, 0.0, 0.0));
    assert(iue::num::isclose(-inf, -inf, 0.0, 0.0));
    assert(!iue::num::isclose(-inf, inf, 0.0, 0.0));
    assert(!iue::num::isclose(inf, -inf, 0.0, 0.0));
  }

  { // nan
    assert(!iue::num::isclose(nan, nan, inf, inf));
  }

  { // around 1.0
    double a = 1.0;
    double b = 1.0 + eps;

    // rel error
    assert(iue::num::isclose(a, b, 0.0, 2 * eps));
    assert(!iue::num::isclose(a, b, 0.0, 0.0));

    // abs error
    assert(iue::num::isclose(a, b, 2 * eps, 0.0));
    assert(!iue::num::isclose(a, b, 0.0, 0.0));
  }

  { // around 1e10
    double a = 1.0 * 1e10;
    double b = (1.0 + eps) * 1e10;

    // rel error
    assert(iue::num::isclose(a, b, 0.0, 2 * eps));
    assert(!iue::num::isclose(a, b, 0.0, 0.0));

    // abs error
    assert(iue::num::isclose(a, b, 1e10 * 2 * eps, 0.0));
    assert(!iue::num::isclose(a, b, 1e9 * 2 * eps, 0.0));
  }

  { // around 1e-10

    double a = 1.0 * 1e-10;
    double b = (1.0 + eps) * 1e-10;

    // rel error
    assert(iue::num::isclose(a, b, 0.0, 2 * eps));
    assert(!iue::num::isclose(a, b, 0.0, 0.0));

    // abs error
    assert(iue::num::isclose(a, b, 1e-10 * 2 * eps, 0.0));
    assert(!iue::num::isclose(a, b, 1e-11 * 2 * eps, 0.0));
  }

  return EXIT_SUCCESS;
}