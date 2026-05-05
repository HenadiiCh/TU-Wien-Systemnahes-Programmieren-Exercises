/// @file
/// @brief Test for Task3

/// @todo Complete all the TODOs in task3.cpp
/// compile & run command from exercise1/:
///   mkdir -p build && g++ -std=c++20 src/task3*.cpp -o build/task3 && ./build/task3

#include "task3.hpp" // add|mul|frac|mean|squared|cubed|eval

#include <cassert>  // assert
#include <cmath>    // std::abs
#include <iostream> // std::cout|endl

int main()
{

    { // testing function 'add'
        double res = add(1, 2, -3);
        assert(std::abs(res - 0.0) < 1e-7);
    }
    { // testing function 'mul'
        double res = mul(2, 3, 4);
        assert(std::abs(res - 24.0) < 1e-7);
    }
    { // testing function 'frac'
        double res = frac(1, 3);
        assert(std::abs(res - (1.0 / 3.0)) < 1e-7);
    }
    { // testing function 'mean'
        double res = mean(10, 90, -10);
        assert(std::abs(res - 30.0) < 1e-7);
    }
    { // testing function 'squared'
        double res = squared(3);
        assert(std::abs(res - 9.0) < 1e-7);
    }
    { // testing function 'cubed'
        double res = cubed(3);
        assert(std::abs(res - 27.0) < 1e-7);
    }
    { // testing function 'cubed'
        double res = eval(10.0, 3, -30, 77);
        assert(std::abs(res - 77) < 1e-7);
    }

    std::cout << "task3.test.cpp: all asserts passed" << "\n";

    return 0;
}
