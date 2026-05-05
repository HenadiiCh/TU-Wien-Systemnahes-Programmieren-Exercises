/// @file
/// @brief Task3: function declarations

#pragma once

/// @brief Calculates the sum of three values
/// @param x 1st value
/// @param y 2nd value
/// @param z 3rd value
/// @return Sum of the three values
double add(double x, double y, double z);

/// @brief Calculates the product of three values
/// @param x 1st value
/// @param y 2nd value
/// @param z 3rd value
/// @return Product of the three values
double mul(double x, double y, double z);

/// @brief Calculates the fraction of two values
/// @param x 1st value
/// @param y 2nd value
/// @return Fraction of x divided by y
double frac(double x, double y);

/// @brief Calculates the average (arithmetic mean) of three values
/// @param x 1st value
/// @param y 2nd value
/// @param z 3rd value
/// @return Average  of the three values
double mean(double x, double y, double z);

/// @brief Calculates the square of a value
/// @param x Value
/// @return Square of x
double squared(double x);

/// @brief Calculates the third power of a value
/// @param x Value
/// @return Cube of x
double cubed(double x);

/// @brief Evaluates a polynomial 'f(x) = a*x^2 + b*x + c'
/// @param x Variable
/// @param a Coefficient
/// @param b Coefficient
/// @param c Coefficient
/// @return Value of the polynomial at x
double eval(double x, double a, double b, double c);
