/// @file
/// @brief Task3: Implemenation

#include "task3.hpp" // solve_quadratic_equation

/// @todo Include standard library headers as needed
#include <cmath> // std::sqrt, NAN

/// @todo Implement both overloads of the function 'solve_quadratic_equation' as declared and specified in task3.hpp
/// Implementation Hints:
/// - a very similar task was part of the exercises in 360058:
///   https://sgit.iue.tuwien.ac.at/360058/homework4/src/commit/aa0a7206bab9e4d19a79fdcebd2c4ac0669c5ae1/src/task2.py#L29
/// - you can set a double to a "quiet Not-a-Number" using this:
///   #include <cmath>  // defines NAN
///   double d = NAN;   // example usage

/// @brief Solves ax^2 + bx + c = 0 using the quadratic formula
std::tuple<double, double> solve_quadratic_equation(double a, double b, double c)
{
    // Compute the discriminant: D = b^2 - 4ac
    double discriminant = b * b - 4.0 * a * c;

    // If D < 0, there are no real solutions — return NaN for both roots
    if (discriminant < 0.0)
        return {NAN, NAN};

    // Compute both roots using the quadratic formula
    double sqrt_d = std::sqrt(discriminant);
    double x1 = (-b - sqrt_d) / (2.0 * a);
    double x2 = (-b + sqrt_d) / (2.0 * a);

    // Return roots in ascending order (smaller first)
    if (x1 > x2)
        return {x2, x1};
    return {x1, x2};
}

/// @brief Overload: accepts coefficients packed as a std::tuple<double,double,double>
std::tuple<double, double> solve_quadratic_equation(std::tuple<double, double, double> abc)
{
    // Unpack the tuple into individual coefficients using structured bindings
    auto [a, b, c] = abc;

    // Delegate to the three-parameter overload above
    return solve_quadratic_equation(a, b, c);
}
