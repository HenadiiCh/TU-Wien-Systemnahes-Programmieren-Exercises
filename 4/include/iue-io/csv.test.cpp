#include "iue-io/csv.hpp"

#include <cassert>  // assert
#include <cstddef>  // std::size_t
#include <iostream> // std::cout|endl
#include <vector>   // std::vector

int main() {

  // prep input data

  std::vector<std::vector<double>> table1;
  {
    auto row = std::vector<double>{1, 2, 3};
    table1.push_back(row);
  }
  {
    auto row = std::vector<double>{10, 20, 30, 40};
    table1.push_back(row);
  }
  {
    auto row = std::vector<double>{1e3, 2e3, 3e3, 4e3};
    table1.push_back(row);
  }

  // write

  try {

    for (const auto& row : table1) {
      for (const auto& value : row)
        std::cout << value << " ";
      std::cout << std::endl;
    }

    iue::io::savecsv("csv_test.csv", table1, ';', 4);

  } catch (const std::exception& e) {
    std::cout << e.what();
  }

  std::vector<std::vector<double>> table2;

  // read

  try {

    table2 = iue::io::loadcsv("csv_test.csv", ';');

    for (const auto& row : table2) {
      for (const auto& value : row)
        std::cout << value << " ";
      std::cout << std::endl;
    }

  } catch (const std::exception& e) {
    std::cout << e.what();
  }

  // compare

  assert(table1.size() == table2.size());

  for (size_t r = 0; r != table1.size(); ++r) {
    assert(table1[r].size() == table2[r].size());
    for (size_t c = 0; c != table1[r].size(); ++c) {
      assert(table1[r][c] == table2[r][c]);
    }
  }

  return 0;
}