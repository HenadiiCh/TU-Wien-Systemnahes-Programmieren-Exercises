/// @file
/// @brief Task1: Single-file executable C++ program using a std::vector<int>
/// compile & run command:
///   mkdir -p build && g++ -std=c++20 src/task1.main.cpp -o build/task1 && ./build/task1

/// @todo Include standard library headers as needed

/// @brief Find the minimum value in a sequence of integer values
/// @param data Sequence of values pass as a std::vector<int> (assertion: sequence is not empty)
/// @return Minimum value in the sequence
/// @todo Implement the function spec above as a funtion `min`

#include <iostream> // for std::cout
#include <vector>   // for std::vector

int min(const std::vector<int> data)
{
    int result = data[0];                  // current minimum = first element
    for (int i = 1; i < data.size(); ++i)  // iterate from the second element to the end
    {
        if (data[i] < result)
        {
            result = data[i]; // found a smaller value — remember it
        }
    }
    return result;
}

int main()
{
    // 1. Create a vector with the required sequence
    std::vector<int> values = {-10, 20, 100, -1024, 2048};

    // 2. & 3. Call min() and capture the result
    int result = min(values);

    // 4. Print the result
    std::cout << "Minimum value: " << result << std::endl;

    return 0;
}