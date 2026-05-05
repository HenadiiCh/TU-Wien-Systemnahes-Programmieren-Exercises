/// @file
/// @brief Task3: implementation

#include "task3.hpp" // add|mul|frac|mean|squared|cubed|eval

/// @todo Include standard library headers as needed

/// @todo define and implement functions 'add|mul|frac|mean|squared|cubed|eval' as declared and
/// specified in task3.hpp

//Calculates the sum of three values
double add(double x, double y, double z)
{
    return x + y + z;
}

//Calculates the product of three values
double mul(double x, double y, double z)
{
    return x * y * z;
}

//Calculates the fraction of two values
double frac(double x, double y)
{
    return x / y;
}

//Calculates the average (arithmetic mean) of three values
double mean(double x, double y, double z)
{
    return (x + y + z) / 3.0;
    // We use 3.0 instead of 3 to explicitly enforce floating-point division.
    // If all operands were integers (int), using just 3 would result in integer 
    // division (e.g., 4 / 3 = 1), truncating the decimal part. By using 3.0 (double), 
    // we ensure the result is correctly calculated as a decimal (e.g., 4.0 / 3.0 = 1.333...).
}

//Calculates the square of a value
double squared(double x)
{
    return x * x;
    // Alternatively, we could also use the standard library function:
    // return std::pow(x, 2);
}

//Calculates the third power of a value
double cubed(double x)
{
    return x * x * x;
    // Alternatively, we could also use the standard library function:
    // return std::pow(x, 3);
}

// Evaluates a polynomial 'f(x) = a*x^2 + b*x + c'
double eval(double x, double a, double b, double c)
{
    return a * x * x + b * x + c;
}
// Alternatively, we could also use the standard library function for powers:
// double eval(double x, double a, double b, double c)
// {
//     return a * std::pow(x, 2) + b * x + c;
// }

//OR we could also use the previously defined functions for squared and mul:
// double eval(double x, double a, double b, double c)
// {
//     return mul(a, squared(x), 1) + mul(b, x, 1) + c;
// }