/// @file
/// @brief Task1: "single-file" excutable C++ program

#include <array> // std::array

/// @todo Include standard library headers as needed
#include <cmath>    // std::sin, std::cos
#include <iostream> // std::cout
#include <numbers>  // std::numbers::pi

namespace task1
{

    using Coord = std::array<double, 2>;

    /// @todo Implement a function 'rotate_counter_clockwise':
    /// - the function receives a two-dimensional coordinate in form of a 'std::array<double, 2>'
    /// - the function receives a rotation angle (in radians) in form of a 'double'
    /// - the function rotates the coordinate counter clockwise around the origin
    /// - the function returns the rotated coordinate as a std::array<double, 2>
    Coord rotate_counter_clockwise(const Coord& coord, double angle)
    {
        // Calculate new X and Y coordinates (Hier berechnen wir die neue X und Y Koordinate)
        double new_x = coord[0] * std::cos(angle) - coord[1] * std::sin(angle);
        double new_y = coord[0] * std::sin(angle) + coord[1] * std::cos(angle);
        return {new_x, new_y};
    }

} // namespace task1

int main()
{
    using namespace task1;

    /// @todo
    /// 1. Create two coordinates (local variables) {112,211} and {-42,23}
    /// 2. Use your 'rotate_counter_clockwise' function to rotate both coordinates by 180 degrees
    /// 3. Capture the results of your function calls in a local variable.
    /// 4. Print the results to the console.
    /// Hint: the expected coordinates after rotating 180 degrees are
    ///   {112,211} -> {-112,-211}
    ///   {-42,23}  -> {42,-23}

    // 1. Create two coordinates (Koordinaten erstellen)
    Coord c1 = {112.0, 211.0};
    Coord c2 = {-42.0, 23.0};

    // 2 & 3. Rotate by 180 degrees and capture results (Rotieren um 180 Grad bzw. Pi)
    Coord rotated_c1 = rotate_counter_clockwise(c1, std::numbers::pi);
    Coord rotated_c2 = rotate_counter_clockwise(c2, std::numbers::pi);

    // 4. Print the results (Ergebnisse auf der Konsole ausgeben)
    std::cout << "Original: {" << c1[0] << ", " << c1[1] << "} -> Rotated: {" << rotated_c1[0] << ", " << rotated_c1[1] << "}\n";
    std::cout << "Original: {" << c2[0] << ", " << c2[1] << "} -> Rotated: {" << rotated_c2[0] << ", " << rotated_c2[1] << "}\n";

    return 0;
}
