#pragma once

#include <stdbool.h> // bool
#include <stdio.h>   // snprintf|stderr
#include <stdlib.h>  // EXIT_FAILURE|EXIT_SUCCESS
#include <string.h>  // strncmp|strlen

/// @brief internal function
static bool iuepo_find_option(const char* option, const char* arg) {
  char buffer[256];
  snprintf(buffer, sizeof(buffer) / sizeof(char), "%s%s", "-", option);
  if (strncmp(buffer, arg, strlen(buffer)) == 0)
    return true;
  snprintf(buffer, sizeof(buffer) / sizeof(char), "%s%s", "--", option);
  if (strncmp(buffer, arg, strlen(buffer)) == 0)
    return true;
  return false;
}

/// @brief internal function
static int iuepo_count_if(const char* option, char** begin, char** end) {
  int res = 0;
  for (char** iter = begin; iter != end; ++iter) {
    if (iuepo_find_option(option, *iter))
      ++res;
  }
  return res;
}

/// @brief internal function
static char** iuepo_find_if(const char* option, char** begin, char** end) {
  int res = 0;
  for (char** iter = begin; iter != end; ++iter) {
    if (iuepo_find_option(option, *iter))
      return iter;
  }
  return end;
}

/// @todo Enum to tag an option as required or optional
enum iuepo_option { IUEPO_REQUIRED = 0, IUEPO_OPTIONAL };

/// @brief Obtain a string-option from command line arguments
/// @param argc Forwarded from the main-function
/// @param argv Forwarded from the main-function
/// @param option Nametag of the option (without dashes)
/// @param default_value Buffer containing the default value for this option
///        if the option is found, the string will be copied into this buffer
/// @param N Length of the buffer 'default_value'
/// @param op Sets this option to required or optional
/// @return returns
///         - true, if the specified command line argument is found (or is optional)
///         - false, if the specified command line argument is not found
static int iuepo_get_string(int argc, char* argv[], const char* option, char* default_value, int N,
                            enum iuepo_option op) {

  int count = iuepo_count_if(option, argv + 1, argv + argc);

  if (count == 0) {
    if (op == IUEPO_REQUIRED) {
      fprintf(stderr, "required option not provided: -/-- %s\n", option);
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  if (count > 1) {
    fprintf(stderr, "option not unique: -/-- %s (count = %i )\n", option, count);
    return EXIT_FAILURE;
  }

  char** iter = iuepo_find_if(option, argv + 1, argv + argc);

  ++iter;

  if (iter == argv + argc) {
    fprintf(stderr, "option not followed by value: -/-- %s\n", option);
    return EXIT_FAILURE;
  }

  if (strncmp("-", *iter, 1) == 0) {
    fprintf(stderr, "option -/-- %s not followed by value but another option -/-- %s\n", option, *iter);
    return EXIT_FAILURE;
  }

  if (snprintf(default_value, N, "%s", *iter) >= N) {
    fprintf(stderr, "provided buffer size %i for option -/-- %s not sufficient\n", N, option);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/// @brief Obtain a char-option from command line arguments
/// @param argc Forwarded from the main-function
/// @param argv Forwarded from the main-function
/// @param option Nametag of the option (without dashes)
/// @param default_value Default value for this option
///        if the option is found, the value will be copied into this buffer
/// @param op Sets this option to required or optional
/// @return returns
///         - true, if the specified command line argument is found (or is optional)
///         - false, if the specified command line argument is not found
/// @note This function warps 'iuepo_get_string' with a subsequent conversion to an char
static int iuepo_get_char(int argc, char* argv[], const char* option, char* default_value, enum iuepo_option op) {

  char default_value_string[256] = "\0";
  snprintf(default_value_string, sizeof(default_value_string), "%c", *default_value);

  if (iuepo_get_string(argc, argv, option, default_value_string, sizeof(default_value_string), op) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  if (strlen(default_value_string) != 1) {
    fprintf(stderr, "value for option -/-- %s is not a single character\n", option);
    return EXIT_FAILURE;
  }

  *default_value = default_value_string[0];

  return EXIT_SUCCESS;
}

/// @brief Obtain a int-option from command line arguments
/// @param argc Forwarded from the main-function
/// @param argv Forwarded from the main-function
/// @param option Nametag of the option (without dashes)
/// @param default_value Default value for this option
///        if the option is found, the value will be copied into this buffer
/// @param op Sets this option to required or optional
/// @return returns
///         - true, if the specified command line argument is found (or is optional)
///         - false, if the specified command line argument is not found
/// @note This function warps 'iuepo_get_string' with a subsequent conversion to an int
static int iuepo_get_int(int argc, char* argv[], const char* option, int* default_value, enum iuepo_option op) {

  char default_value_string[256] = "\0";
  snprintf(default_value_string, sizeof(default_value_string), "%i", *default_value);

  if (iuepo_get_string(argc, argv, option, default_value_string, sizeof(default_value_string), op) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  int res = sscanf(default_value_string, "%i", default_value);

  if (res != 1) {
    fprintf(stderr, "value for option -/-- %s could not be converted\n", option);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/// @brief Obtain a double-option from command line arguments
/// @param argc Forwarded from the main-function
/// @param argv Forwarded from the main-function
/// @param option Nametag of the option (without dashes)
/// @param default_value Default value for this option
///        if the option is found, the value will be copied into this buffer
/// @param op Sets this option to required or optional
/// @return returns
///         - true, if the specified command line argument is found (or is optional)
///         - false, if the specified command line argument is not found
/// @note This function warps 'iuepo_get_string' with a subsequent conversion to a double
static int iuepo_get_double(int argc, char* argv[], const char* option, double* default_value, enum iuepo_option op) {

  char default_value_string[256] = "\0";
  snprintf(default_value_string, sizeof(default_value_string), "%lf", *default_value);

  if (iuepo_get_string(argc, argv, option, default_value_string, sizeof(default_value_string), op) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  int res = sscanf(default_value_string, "%lf", default_value);

  if (res != 1) {
    fprintf(stderr, "value for option -/-- %s could not be converted\n", option);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}