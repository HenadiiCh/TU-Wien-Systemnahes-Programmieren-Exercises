#include "iue-po/cpo.h"

#include <assert.h> // assert
#include <math.h>   // fabs
#include <stdio.h>  // printf
#include <stdlib.h>
#include <string.h> // strcmp

int main(int argc, char* argv[]) {

  char value1[256] = "default1";
  if (iuepo_get_string(argc, argv, "option1", value1, sizeof(value1), IUEPO_REQUIRED) != EXIT_SUCCESS)
    return EXIT_FAILURE;

  int value2 = 1;
  if (iuepo_get_int(argc, argv, "option2", &value2, IUEPO_REQUIRED) != EXIT_SUCCESS)
    return EXIT_FAILURE;

  char value3 = 'x';
  if (iuepo_get_char(argc, argv, "option3", &value3, IUEPO_REQUIRED) != EXIT_SUCCESS)
    return EXIT_FAILURE;

  double value4 = 1.0;
  if (iuepo_get_double(argc, argv, "option4", &value4, IUEPO_REQUIRED) != EXIT_SUCCESS)
    return EXIT_FAILURE;

  double value5 = 1e100;
  if (iuepo_get_double(argc, argv, "option5", &value5, IUEPO_OPTIONAL) != EXIT_SUCCESS)
    return EXIT_FAILURE;

  printf("'%s'\n", value1);
  printf("'%i'\n", value2);
  printf("'%c'\n", value3);
  printf("'%lf'\n", value4);

  assert(strcmp(value1, "o1") == 0);
  assert(value2 == 100);
  assert(value3 == 'X');
  assert(fabs(value4 - 1.0e-7) < 1e-13);
  assert(fabs(value5 - 1e100) < 1e-13);

  return EXIT_SUCCESS;
}
