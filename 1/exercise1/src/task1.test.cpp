/// @file
/// @brief This program gathers compile-time information such as compilation date,
/// time, compiler version, language standard level, and source file name.
/// It writes these details to "task1_output_cpp.txt" and validates that
/// the compiler supports at least the C++20 language standard.

/// @todo Ensure you can compile and run this C++ program in your environment. Suggested
/// compile & run command from exercise1/:
///   mkdir -p build output && g++ -std=c++20 src/task1.test.cpp -o build/task1cpp && ./build/task1cpp

#include <cassert>    // assert
#include <filesystem> // std::filesystem::path
#include <fstream>    // std::ofstream
#include <iostream>   // std::cout
#include <sstream>    // std::ostringstream
#include <version>    // feature test macros

const static char* compiler =
#if defined(__clang__)
    "Clang " __clang_version__;
#elif defined(__GNUC__)
    "GCC " __VERSION__;
#elif defined(_MSC_VER)
    "MSVC";
#else
    "Unknown compiler";
#endif

int main()
{

    std::ostringstream oss;

    oss << "This compilation unit ( " << __FILE__ << " ) was compiled\n";
    oss << "  - on " << __DATE__ << " at " << __TIME__ << "\n";
    oss << "  - using the " << compiler << " compiler,\n";
    oss << "  - and the C++ language standard " << __cplusplus << ".\n";

    std::filesystem::path filename = "output/task1_output_cpp.txt";
    std::ofstream ofs(filename);
    ofs << oss.str();

    assert(__cplusplus >= 202002L);

    std::cout << "task1.test.cpp: all asserts passed\n";
    return 0;
}