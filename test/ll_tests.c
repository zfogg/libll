#include <stdlib.h>
#include <stdio.h>

#include "../lib/ll.h"
#include "ll_tests.h"

#include "ll_tests_0.c"
#include "ll_tests_1.c"
#include "ll_tests_2.c"
#include "ll_tests_3.c"

#include "ll_tests_diagnostics.c"


int main(int argc, const char* argv[]) {
    int const testValue = argc > 1 ? atoi(argv[1]) : 9377;

    puts("\nTesting linked list functionality . . .\n");

    // Level 0
    LL_length_test(testValue);
    LL_last_test(testValue);
    LL_reverse_test(testValue);
    LL_ofIndex_test(testValue);
    LL_indexOf_test(testValue);
    LL_find_test(testValue);
    LL_findBefore_test(testValue);

    // Level 1
    LL_push_test(testValue);
    LL_pop_test(testValue);
    LL_free_test(testValue);
    LL_concat_test(testValue);
    LL_lastN_test(testValue);
    LL_toArray_test(testValue);
    LL_split_test(testValue);
    LL_freeAll_test(testValue);
    LL_findAll_test(testValue);

    // Level 2
    LL_pushMany_test(testValue);
    LL_popMany_test(testValue);
    LL_freeMany_test(testValue);
    LL_insertAfter_test(testValue);
    LL_insertAtIndex_test(testValue);

    // Level 3
    LL_forEach_test(testValue);

    // Diagnostics
    puts("");
    processTestResults("Pass ALL the tests", testResults);

    return 0;
}

