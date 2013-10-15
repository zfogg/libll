#ifndef ll_tests_h__
#define ll_tests_h__

#include "../lib/ll.h"


// Level 0

void LL_length_test             (int count);

void LL_last_test               (int count);

void LL_reverse_test            (int count);

void LL_ofIndex_test            (int count);

void LL_indexOf_test            (int count);

void LL_find_test               (int count);

void LL_findBefore_test         (int count);


// Level 1

void LL_push_test               (int count);

void LL_pop_test                (int count);

void LL_free_test               (int count);

void LL_concat_test             (int count);

void LL_lastN_test              (int count);

void LL_toArray_test            (int count);

void LL_split_test              (int count);

void LL_freeAll_test            (int count);

void LL_findAll_test            (int count);


// Level 2

void LL_pushMany_test           (int count);

void LL_popMany_test            (int count);

void LL_freeMany_test           (int count);

void LL_insertAtIndex_test      (int count);

void LL_insertAfter_test        (int count);


// Level 3

LL_value_t* testF_Values;

int forEach_validationCallback_results;

void LL_forEach_test            (int count);

void forEach_callback           (nodePtr* head, nodePtr n);

void forEach_validationCallback (nodePtr* head, nodePtr n);


// Diagnostics

#define WHITE_CC "\e[0m"

#define GREEN_CC "\e[32m"

#define RED_CC   "\e[31m"

extern int LL_testResults;

void processTestResults         (const char* testName, int results);

nodePtr newTestLL               (int count);

LL_value_t randTestVal          ();


#endif // ll_tests_h__

