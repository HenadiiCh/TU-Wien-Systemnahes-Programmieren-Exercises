/// @file
/// @brief Test for iuenum_islcose

#include "iue-num/numerics.h" // iuenum_islcose, iuenum_islcose_tol

#include <assert.h> // assert
#include <float.h>  // DBL_EPSILON
#include <math.h>   // NAN, INFINITY
#include <stdlib.h> // EXIT_SUCCESS

int main() {

  const double eps = DBL_EPSILON;
  const double inf = INFINITY;
  const double nan = NAN;

  { // infinity

    assert(iuenum_isclose_tol(inf, inf, 0.0, 0.0));
    assert(iuenum_isclose_tol(-inf, -inf, 0.0, 0.0));
    assert(!iuenum_isclose_tol(-inf, inf, 0.0, 0.0));
    assert(!iuenum_isclose_tol(inf, -inf, 0.0, 0.0));
  }

  { // nan
    assert(!iuenum_isclose_tol(nan, nan, inf, inf));
  }

  { // around 1.0
    double a = 1.0;
    double b = 1.0 + eps;

    // rel error
    assert(iuenum_isclose_tol(a, b, 0.0, 2 * eps));
    assert(!iuenum_isclose_tol(a, b, 0.0, 0.0));

    // abs error
    assert(iuenum_isclose_tol(a, b, 2 * eps, 0.0));
    assert(!iuenum_isclose_tol(a, b, 0.0, 0.0));
  }

  { // around 1e10
    double a = 1.0 * 1e10;
    double b = (1.0 + eps) * 1e10;

    // rel error
    assert(iuenum_isclose_tol(a, b, 0.0, 2 * eps));
    assert(!iuenum_isclose_tol(a, b, 0.0, 0.0));

    // abs error
    assert(iuenum_isclose_tol(a, b, 1e10 * 2 * eps, 0.0));
    assert(!iuenum_isclose_tol(a, b, 1e9 * 2 * eps, 0.0));
  }

  { // around 1e-10

    double a = 1.0 * 1e-10;
    double b = (1.0 + eps) * 1e-10;

    // rel error
    assert(iuenum_isclose_tol(a, b, 0.0, 2 * eps));
    assert(!iuenum_isclose_tol(a, b, 0.0, 0.0));

    // abs error
    assert(iuenum_isclose_tol(a, b, 1e-10 * 2 * eps, 0.0));
    assert(!iuenum_isclose_tol(a, b, 1e-11 * 2 * eps, 0.0));
  }

  return EXIT_SUCCESS;
}