#pragma once

#include <filesystem> // std::filesystem::path
#include <fstream>    // std::ofstream|ifstream
#include <iomanip>    // std::scientifc|setprecision
#include <iostream>   // std::cout|endl
#include <sstream>    // std::istringstream|ostringstream
#include <string>     // std::string
#include <vector>     // std::vector

// std::ios::badbit|failbit|eofbit https://en.cppreference.com/w/cpp/io/ios_base/iostate

namespace iue::io {

/// @brief Writes a numeric values to a file using a csv-format
/// @param filepath file to be written including the desired extension
/// @param table table with the rows to be written
/// @param del delimiter between individual values
/// @param precision (number of decimal digits)
inline void savecsv(std::filesystem::path filepath, const std::vector<std::vector<double>>& table,
                    char del = ' ', int precision = 18) {

  auto serialize = [del, precision](const std::vector<double>& row) -> std::string {
    auto oss = std::ostringstream{};
    oss.exceptions(std::ios::badbit | std::ios::failbit);
    for (auto value : row)
      oss << std::scientific << std::setprecision(precision) << value << del;
    auto res = oss.str();
    res.pop_back();
    return res;
  };

  auto ofs = std::ofstream{};
  ofs.exceptions(std::ios::badbit | std::ios::failbit);
  ofs.open(filepath);

  for (const auto& row : table)
    ofs << serialize(row) << std::endl;
}

/// @brief Read numeric values stored in a csv-format
/// @param filepath input file containing the numeric values
/// @param del delimiter between individual values
/// @return table which was read
inline std::vector<std::vector<double>> loadcsv(std::filesystem::path filepath, char del = ' ') {

  auto deserialize = [del](const std::string& strrow) -> std::vector<double> {
    auto iss = std::istringstream{strrow};
    iss.exceptions(std::ios::badbit);
    std::vector<double> row;
    std::string strvalue;
    while (std::getline(iss, strvalue, del)) {
      std::istringstream iss{strvalue};
      iss.exceptions(std::ios::badbit | std::ios::failbit);
      double value;
      iss >> value;
      row.push_back(value);
    }
    iss.clear();
    iss.exceptions(std::ios::badbit | std::ios::failbit);
    return row;
  };

  std::ifstream ifs;
  ifs.exceptions(std::ios::badbit | std::ios::failbit);
  ifs.open(filepath);

  std::vector<std::vector<double>> table;
  std::string strrow;
  ifs.exceptions(std::ios::badbit);
  while (std::getline(ifs, strrow)) {
    table.push_back(deserialize(strrow));
  }
  ifs.clear();
  ifs.exceptions(std::ios::badbit | std::ios::failbit);
  return table;
}

} // namespace iue::io
