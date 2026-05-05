/// @file
/// @brief This program creates "task1_output_c.txt" and writes details about
/// when the program was compiled, which C standard was used, and which source
/// file contains the main function. It then asserts that the compiler supports
/// at least the C11 standard and prints a confirmation message if all checks
/// pass.

/// @todo Ensure you can compile and run this C program in your environment.
/// compile & run command from exercise1/:
///   mkdir -p build output && gcc -std=c11 src/task1.test.c -o build/task1c && ./build/task1c

#include <assert.h> // assert
#include <stdio.h>  // FILE
#include <stdlib.h> // EXIT_FAILURE|EXIT_SUCCESS

static const char* compiler =
#if defined(__clang__)
    "Clang " __clang_version__;
#elif defined(__GNUC__)
    "GCC " __VERSION__;
#elif defined(_MSC_VER)
    "MSVC";
#else
    "Unknown compiler";
#endif

int main(void)
{

    FILE* stream = fopen("output/task1_output_c.txt", "w");
    if (stream == NULL)
        return EXIT_FAILURE;

    fprintf(stream, "This compilation unit ( %s ) was compiled\n", __FILE__);
    fprintf(stream, "  - on %s at %s,\n", __DATE__, __TIME__);
    fprintf(stream, "  - using the %s compiler,\n", compiler);
    fprintf(stream, "  - the C language standard %li.\n", __STDC_VERSION__);

    fclose(stream);

    assert(__STDC_VERSION__ >= 201112L);

    printf("task1.test.c: all asserts passed\n");

    return EXIT_SUCCESS;
}
