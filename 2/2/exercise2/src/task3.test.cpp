/// @file
/// @brief Task3: Tests 
/// compile & run command:
///   mkdir -p build && g++ -std=c++20 src/task3*.cpp -o build/task3 && ./build/task3

#include "task3.hpp" // solve_quadratic_equation

#include <cassert>  // assert
#include <cmath>    // NAN
#include <iostream> // std::cout|endl

int main() {

  { // testing function overloads 'solve_quadratic_equation'
    auto [s1, s2] = solve_quadratic_equation(1.0, 3.0, 2.0);
    assert(std::abs(s1 - (-2.0)) < 1e-7);
    assert(std::abs(s2 - (-1.0)) < 1e-7);
  }

  { // testing function overloads 'solve_quadratic_equation'
    std::tuple<double, double, double> coefficients = {1.0, 3.0, 2.0};
    auto [s1, s2] = solve_quadratic_equation(coefficients);
    assert(std::abs(s1 - (-2.0)) < 1e-7);
    assert(std::abs(s2 - (-1.0)) < 1e-7);
  }

  { // testing function overloads 'solve_quadratic_equation'
    auto [s1, s2] = solve_quadratic_equation(1.0, 2.0, 5.0);
    assert(std::isnan(s1));
    assert(std::isnan(s2));
  }

  { // testing function overloads 'solve_quadratic_equation'
    std::tuple<double, double, double> coefficients = {1.0, 2.0, 5.0};
    auto [s1, s2] = solve_quadratic_equation(coefficients);
    assert(std::isnan(s1));
    assert(std::isnan(s2));
  }

  { // testing function overloads 'solve_quadratic_equation'
    auto [s1, s2] = solve_quadratic_equation(2.0, 1.0, -3.0);
    assert(std::abs(s1 - (-1.5)) < 1e-7);
    assert(std::abs(s2 - (1.0)) < 1e-7);
  }

  { // testing function overloads 'solve_quadratic_equation'
    std::tuple<double, double, double> coefficients = {2.0, 1.0, -3.0};
    auto [s1, s2] = solve_quadratic_equation(coefficients);
    assert(std::abs(s1 - (-1.5)) < 1e-7);
    assert(std::abs(s2 - (1.0)) < 1e-7);
  }

  std::cout << "task3.test.cpp: all asserts passed" << std::endl;

  return 0;
}
