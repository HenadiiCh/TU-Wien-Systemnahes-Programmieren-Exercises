/// @file
/// @brief Task2: Implemenation

#include "task2.hpp" // count_gt|count_lt|select_gt|select_lt|select_gt_and_lt|mean|median|minmax

/// @todo Include standard library headers as needed
#include <algorithm> // std::ranges::sort (used for median)

/// @todo define and implement functions 'count_gt|count_lt|select_gt|select_lt|select_gt_and_lt|mean|median|minmax' as
/// declared and specified in task2.hpp
/// Implementation Hints:
/// - Median calculation: 
///   - you can inplace-sort your sequence using 'std::ranges::sort(data);' 
///   - you need to '#include <algorithm>' for this

/// @brief Counts how many values are greater than the reference value
int count_gt(std::vector<double> data, double ref)
{
    int count = 0;
    // Increment counter for each element strictly greater than ref
    for (double val : data)
    {
        if (val > ref)
            ++count;
    }
    return count;
}

/// @brief Counts how many values are less than the reference value
int count_lt(std::vector<double> data, double ref)
{
    int count = 0;
    // Increment counter for each element strictly less than ref
    for (double val : data)
    {
        if (val < ref)
            ++count;
    }
    return count;
}

/// @brief Selects (copies) values that are greater than the reference value
std::vector<double> select_gt(std::vector<double> data, double ref)
{
    std::vector<double> result;
    // Add element to result only if it is strictly greater than ref
    for (double val : data)
    {
        if (val > ref)
            result.push_back(val);
    }
    return result;
}

/// @brief Selects (copies) values that are less than the reference value
std::vector<double> select_lt(std::vector<double> data, double ref)
{
    std::vector<double> result;
    // Add element to result only if it is strictly less than ref
    for (double val : data)
    {
        if (val < ref)
            result.push_back(val);
    }
    return result;
}

/// @brief Selects (copies) values that lie strictly between lower and upper
std::vector<double> select_gt_and_lt(std::vector<double> data, double lower, double upper)
{
    std::vector<double> result;
    // Element must be greater than lower AND less than upper
    for (double val : data)
    {
        if (val > lower && val < upper)
            result.push_back(val);
    }
    return result;
}

/// @brief Calculates the arithmetic mean of the sequence
double mean(std::vector<double> data)
{
    double sum = 0.0;
    // Sum all elements, then divide by the count
    for (double val : data)
        sum += val;
    return sum / (double)data.size();
}

/// @brief Calculates the median of the sequence
double median(std::vector<double> data)
{
    // Sort the data in-place so we can find the middle element(s)
    std::ranges::sort(data);

    int n = (int)data.size();
    if (n % 2 == 1)
    {
        // Odd count: the median is the single middle element
        return data[n / 2];
    }
    else
    {
        // Even count: the median is the average of the two middle elements
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    }
}

/// @brief Finds the minimum and maximum value in the sequence
std::tuple<double, double> minmax(std::vector<double> data)
{
    // Initialise both min and max with the first element
    double min_val = data[0];
    double max_val = data[0];

    // Update min/max as we scan the rest of the sequence
    for (double val : data)
    {
        if (val < min_val)
            min_val = val;
        if (val > max_val)
            max_val = val;
    }

    // Return as a tuple: (minimum, maximum)
    return {min_val, max_val};
}
