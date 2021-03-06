#include <stdio.h>
#include <stdlib.h>

#include "../src/ll.h"
#include "../src/ll_0.h"
#include "../src/ll_1.h"
#include "../src/ll_2.h"
#include "../src/ll_3.h"
#include "ll_tests.h"
#include "ll_tests_debug.h"


void processTestResults(const char* testName, int results) {
    const char* color = results ? GREEN_CC : RED_CC;
    const char* text  = results ? "pass" : "fail";
    printf("\tTesting - %-30s: %s%s%s\n", testName, color, text, WHITE_CC);
    LL_testResults &= results;
}


nodePtr newTestLL(int count) {
    nodePtr head = NULL;
    LL_push(&head, randTestVal());

    int i, j;
    for (i = 1, j = 0; i < count; i++, j++)
        LL_push(&head, randTestVal());
    // Assuming LL_value_t is of type int.

    return head;
}


LL_value_t randTestVal() {
    // Produces a random char that satisfies [a-zA-Z].
    LL_value_t c = rand() % 52;
    c += c < 26 ? 'a' : 'A';
    return c;
}

