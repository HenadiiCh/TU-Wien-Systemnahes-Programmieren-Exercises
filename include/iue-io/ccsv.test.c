#include "iue-io/ccsv.h"

#include <assert.h> // assert
#include <stddef.h> // size_t

int main(void) {

  // prep input data

  struct Table table1 = {NULL, 0};
  {
    double data[3] = {1, 2, 3};
    table_append_copy(&table1, data, 3);
  }
  {
    double data[4] = {0.1, 20, 30, 40};
    table_append_copy(&table1, data, 4);
  }
  {
    double data[4] = {1e3, 2e3, 3e3, 4e3};
    table_append_copy(&table1, data, 4);
  }

  { // write

    int res = iueio_savecsv("ccsv_test.csv", &table1, ';', 5);

    if (res != EXIT_SUCCESS) {
      fprintf(stderr, "error saving file.\n");
      exit(EXIT_FAILURE);
    }
  }

  struct Table table2 = {NULL, 0};

  { // read

    int res = iueio_loadcsv("ccsv_test.csv", &table2, ';');

    if (res != EXIT_SUCCESS) {
      fprintf(stderr, "error loading file.\n");
      exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i != table2.n; ++i) {
      for (size_t j = 0; j != table2.rows[i].n; ++j)
        printf("%lf ", table2.rows[i].values[j]);
      printf("\n");
    }
  }

  // compare

  assert(table1.n == table2.n);

  for (size_t r = 0; r != table1.n; ++r) {
    assert(table1.rows[r].n == table2.rows[r].n);
    for (size_t c = 0; c != table1.rows[r].n; ++c) {
      assert(table1.rows[r].values[c] == table2.rows[r].values[c]);
    }
  }

  table_clear(&table1);
  table_clear(&table2);

  return EXIT_SUCCESS;
}