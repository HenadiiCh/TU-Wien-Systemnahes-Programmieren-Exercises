/// @file
/// @brief Task2: function declarations

#pragma once

#include <tuple>  // std::tuple
#include <vector> // std::vector

/// @brief Counts how many values in a sequence are greater than (gt) a reference value
/// @param data Sequence of values
/// @param ref Reference value
/// @return Number of values in the sequence, which are greater than than ref
int count_gt(std::vector<double> data, double ref);

/// @brief Counts how many values in a sequence are less than (lt) a reference value
/// @param data Sequence of values
/// @param ref Reference value
/// @return Number of values in the sequence, which are less than than ref
int count_lt(std::vector<double> data, double ref);

/// @brief Selects values from a sequence which are greater than (gt) a reference value
/// @param data Sequence of values
/// @param ref Reference value
/// @return Sequence of selected (copied) values in the order of occurence in the original sequence
std::vector<double> select_gt(std::vector<double> data, double ref);

/// @brief Selects values from a sequence which are less than (lt) a reference value
/// @param data Sequence of values
/// @param ref Reference value
/// @return Sequence of selected (copied) values in the order of occurence in the original sequence
std::vector<double> select_lt(std::vector<double> data, double ref);

/// @brief Selects values from a sequence which are bounded by two reference values
/// @param data Sequence of values
/// @param lower Lower bound
/// @param upper Upper bound
/// @return Sequence of selected (copied) values in the order of occurence in the original sequence
std::vector<double> select_gt_and_lt(std::vector<double> data, double lower, double upper);

/// @brief Calculates the mean for a sequence of values
/// @param data Sequence of values; assertion: data.size() >= 1
/// @return Mean value (arithmetic mean)
double mean(std::vector<double> data);

/// @brief Calculate the median for a sequence of numbers
/// @param data Sequence of values; assertion: data.size() >= 1
/// @return Median value:
///    - if the length of the sequence is odd, the median value is "the middle value", else
///    - if the length of the sequence is even, the median value is the average of the "two middle values"
double median(std::vector<double> data);

///
/// @brief Finds the minimum and maximum value
/// @param data Sequence of values; assertion: data.size() >= 1
/// @return Tuple with the minimum and maximum value (in this order)
std::tuple<double, double> minmax(std::vector<double> data);
