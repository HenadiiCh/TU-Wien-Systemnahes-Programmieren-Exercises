#pragma once

#include <assert.h> // assert
#include <math.h>   // NAN
#include <stddef.h> // size_t
#include <stdio.h>  // FILE|snprintf
#include <stdlib.h> // EXIT_FAILURE|EXIT_SUCCESS
#include <string.h> // strtok|strdup|memcpy

/// @brief Sequence of values
struct Row {
  double* values; ///< owning pointer to an array of values
  size_t n;       ///< length of array 'value'
};

/// @brief Sequence of rows
struct Table {
  struct Row* rows; ///< owning pointer to an array of rows
  size_t n;         ///< length of array 'rows'
};

/// @brief Deallocates all owning pointers held by a table and its rows
static void table_clear(struct Table* table) {
  for (size_t i = 0; i != table->n; ++i) {
    free(table->rows[i].values);
  }
  free(table->rows);
  table->rows = NULL;
  table->n = 0;
}

/// @brief Appends a Row to a Table by copying the provided data to a newly allocated Row
static void table_append_copy(struct Table* table, const double* data, size_t n) {
  assert(table != NULL);
  table->rows = realloc(table->rows, sizeof(struct Row) * ++table->n);
  double* ptr = malloc(sizeof(double) * n);
  memcpy(ptr, data, sizeof(double) * n);
  table->rows[table->n - 1].values = ptr;
  table->rows[table->n - 1].n = n;
}

/// @brief Appends a Row to a Table by transferring ownership of a provided, already dynamically allocated Row
static void table_append_move(struct Table* table, const struct Row* row) {
  assert(table != NULL);
  table->rows = realloc(table->rows, sizeof(struct Row) * ++table->n);
  table->rows[table->n - 1] = *row;
}

/// @brief Deserialize a row from a string into a stream
static void row_serialize(const struct Row* row, FILE* stream, char del, unsigned int precision) {
  char format[32];
  // generate dynamic format string, e.g. "%.18e;" for del = ';' and precision = 18
  snprintf(format, sizeof(format) / sizeof(char), "%%.%ue%c", precision, del);
  for (size_t r = 0; r != row->n - 1; ++r) {
    fprintf(stream, format, row->values[r], del);
  }
  snprintf(format, sizeof(format) / sizeof(char), "%%.%ue", precision);
  fprintf(stream, format, row->values[row->n - 1]); // avoid trailing delimiter
  fprintf(stream, "\n");
}

/// @brief Writes a numeric values to a file using a csv-format
/// @param filepath file to be written including the desired extension
/// @param table table with the rows to be written
/// @param del delimiter between individual values
/// @param precision (number of decimal digits)
static int iueio_savecsv(const char* filepath, const struct Table* table, char del, unsigned int precision) {

  // open file
  FILE* stream = fopen(filepath, "w");
  if (stream == NULL)
    return EXIT_FAILURE;

  // write data
  for (size_t i = 0; i != table->n; ++i) {
    row_serialize(&table->rows[i], stream, del, precision);
  }

  fclose(stream);
  return EXIT_SUCCESS;
}

/// @brief Serializes a Row from a stream
static int row_deserialize(struct Row* row, char* line, char del) {
  assert(row->n == 0);
  double value = NAN;
  int n = 0;
  char delims[2] = {del, '\0'};
  for (char* iter = strtok(line, delims); iter != NULL; iter = strtok(NULL, delims)) {
    if (*iter == '\n')
      return n; // trailing delimiter
    if (sscanf(iter, "%lf", &value) != 1)
      return -1; // conversion failed 
    row->values = realloc(row->values, sizeof(double) * ++row->n);
    row->values[row->n - 1] = value;
    ++n;
  }
  return n;
}

/// @brief Read numeric values stored in a csv-format
/// @param filepath input file containing the numeric values
/// @param table table to be read into (must be empty)
/// @param del delimiter between individual values in a row
/// @return integral values signalling success or failure
static int iueio_loadcsv(const char* filepath, struct Table* table, char del) {

  // check if table is empty
  assert(table->n == 0);

  // open file
  FILE* stream = fopen(filepath, "r");
  if (stream == NULL)
    return EXIT_FAILURE;

  // read from stream row-by-row (fixed size buffer)
  char line[1024];
  line[1023] = '\n';

  // read each line into a row
  while (fgets(&line[0], sizeof(line) / sizeof(char), stream)) {
    if (!(line[1023] == '\n'))
      return EXIT_FAILURE;
    struct Row row = {NULL, 0};
    int n = row_deserialize(&row, line, del);
    if (n < 0)
      return EXIT_FAILURE;
    table_append_move(table, &row);
  }

  fclose(stream);
  return EXIT_SUCCESS;
}