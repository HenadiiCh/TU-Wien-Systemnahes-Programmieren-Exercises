/// @file
/// @brief Task3: tests

#include "task3.hpp" // task3::render_something

#include <cassert>    // assert
#include <filesystem> // std::filesystem::exists
#include <iostream>   // std::cout, sts::endl

int main()
{

    std::string filepath = "output/task3.test.svg";

    std::filesystem::remove(filepath);
    int count = task3::render_something(filepath);
    assert(std::filesystem::exists(filepath));
    assert(count >= 200);

    std::cout << "task3.test.cpp: all asserts passed" << std::endl;

    return 0;
}
