/// @file
/// @brief Task2: Tests
/// compile & run command:
///   mkdir -p build && g++ -std=c++20 src/task2*.cpp -o build/task2 && ./build/task2

#include "task2.hpp" // count_gt|count_lt|select_gt|select_lt|select_gt_and_lt|mean|median|minmax

#include <cassert>  // assert
#include <iostream> // std::cout|endl

int main()
{

    { // testing function 'count_gt'
        int res = count_gt({1.0, 2.0, 3.0, 4.0}, 2.0);
        assert(res == 2);
    }

    { // testing function 'count_gt'
        int res = count_gt({-4.0, -2.0, -2.0, -1.0}, -2.0);
        assert(res == 1);
    }

    { // testing function 'count_lt'
        int res = count_lt({-4.0, -2.0, -2.0, -1.0}, -1.0);
        assert(res == 3);
    }

    { // testing function 'count_lt'
        int res = count_lt({2.0, 2.0, 2.0, 2.0}, 3.0);
        assert(res == 4);
    }

    { // testing function 'select_lt'
        std::vector<double> res = select_lt({2.0, 2.0, 2.0, 2.0}, 3.0);
        std::vector<double> expected = {2.0, 2.0, 2.0, 2.0};
        assert(res == expected);
    }

    { // testing function 'select_lt'
        std::vector<double> res = select_lt({1.0, 2.0, 3.0, 4.0}, 4.0);
        std::vector<double> expected = {1.0, 2.0, 3.0};
        assert(res == expected);
    }

    { // testing function 'select_gt'
        std::vector<double> res = select_gt({2.0, 2.0, 2.0, 2.0}, 2.0);
        std::vector<double> expected = {};
        assert(res == expected);
    }

    { // testing function 'select_gt'
        std::vector<double> res = select_gt({1.0, 2.0, 3.0, 4.0}, 2.0);
        std::vector<double> expected = {3.0, 4.0};
        assert(res == expected);
    }

    { // testing function 'select_gt_and_lt'
        std::vector<double> res = select_gt_and_lt({-3.0, 2.0, -3.0, -2.0, 4.0, 1.0, -1.0, -4.0}, -3.0, 3.0);
        std::vector<double> expected = {2.0, -2.0, 1.0, -1.0};
        assert(res == expected);
    }

    { // testing function 'mean'
        double res = mean({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 0.0});
        double expected = 3.0;
        assert(std::abs(res - expected) < 1e-7);
    }

    { // testing function 'mean'
        double res = mean({-3.0, -2.0, -1.0, 1.0, 2.0, 3.0});
        double expected = 0.0;
        assert(std::abs(res - expected) < 1e-7);
    }

    { // testing function 'median'
        double res = median({3.0});
        double expected = 3.0;
        assert(std::abs(res - expected) < 1e-7);
    }

    { // testing function 'median'
        double res = median({2.0, 3.0});
        double expected = 2.5;
        assert(std::abs(res - expected) < 1e-7);
    }

    { // testing function 'median'
        double res = median({3.0, 2.0, 3.0, 2.0});
        double expected = 2.5;
        assert(std::abs(res - expected) < 1e-7);
    }

    { // testing function 'median'
        double res = median({3.0, 3.0, 3.0, -1.0, 4.0});
        double expected = 3.0;
        assert(std::abs(res - expected) < 1e-7);
    }

    { // testing function 'minmax'
        std::tuple<double, double> res = minmax({300.0, 100.0});
        std::tuple<double, double> expected = {100.0, 300.0};
        assert(res == expected);
    }

    { // testing function 'minmax'
        std::tuple<double, double> res = minmax({-1.0, -2.0, -3.0, 4.0, 20.0, 12.0});
        std::tuple<double, double> expected = {-3.0, 20.0};
        assert(res == expected);
    }

    std::cout << "task2.test.cpp: all asserts passed" << "\n";

    return 0;
}
