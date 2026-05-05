/// @file Task2.cpp
/// @brief Single-file executable C++ program summing two integers

/// @todo Complete all the TODOs, compile/run your program
/// compile & run command from exercise1/:
///   mkdir -p build && g++ -std=c++20 src/task2.main.cpp -o build/task2 && ./build/task2

/// @todo Include headers as needed

/// @brief Calculate the sum of two integers
/// @param a first integer
/// @param b second integer
/// @return sum of a and b
/// @todo Implement this function spec as a funtion `add`

#include <iostream>

//function add - takes two integers as input and returns their sum

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 33; //first integer
    int b = 6600; //second integer

    int c = add(a, b); // Sum them via your `add` function.

    std::cout << "The sum of " << a << " and " << b << " is: " << c << std::endl; // Print the result to the console.
    return 0;
}