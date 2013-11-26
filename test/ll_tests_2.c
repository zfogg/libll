#include <stdlib.h>

#include "../src/ll.h"
#include "../src/ll_0.h"
#include "../src/ll_1.h"
#include "../src/ll_2.h"
#include "../src/ll_3.h"
#include "ll_tests.h"
#include "ll_tests_debug.h"


void LL_pushMany_test(int count) {
  (void)(count);
}


void LL_popMany_test(int count) {
    nodePtr head = newTestLL(count);
    int index = count / 2;
    LL_value_t* lastCountValues   = LL_toArray(LL_lastN(head, index)),
        * poppedCountValues = LL_popMany(&head, index);

    int results, i;
    for (results = 1, i = 0; i < index; i++)
        results &= poppedCountValues[i] == lastCountValues[i];

    free(poppedCountValues);
    free(lastCountValues);

    processTestResults("popMany", results);
    LL_freeAll(&head);
}


void LL_freeMany_test(int count) {
    nodePtr head = newTestLL(count),
            n    = head->next;

    LL_freeMany(&head, &n, count / 2);

    processTestResults("freeMany", LL_find(head, n) == NULL);
    LL_freeAll(&head);
}


void LL_insertAfter_test(int count) {
    nodePtr head = newTestLL(count);
    int results = 1;

    results &= head->next->value != count;

    LL_value_t testV = randTestVal();
    LL_insertAfter(&head, testV);

    results &= head->next->value == testV;

    processTestResults("insertAfter", results);
    LL_freeAll(&head);
}


void LL_insertAtIndex_test(int count) {
    nodePtr head = newTestLL(count);

    LL_insertAtIndex(&head, head->value, 0);

    processTestResults("insertAtIndex - before head",
            head->value == head->next->value);

    // A value several nodes into the list.
    LL_value_t valueToFind = head->next->next->value;
    nodePtr beforeInsert = LL_findAll(head, valueToFind);
    LL_insertAtIndex(&head, valueToFind, count / 2);
    nodePtr afterInsert = LL_findAll(head, valueToFind);

    processTestResults("insertAtIndex - between nodes",
            LL_length(beforeInsert)+1 == LL_length(afterInsert));
    LL_freeAll(&beforeInsert);
    LL_freeAll(&afterInsert);

    nodePtr last = LL_last(head);
    LL_insertAtIndex(&head, last->value, LL_length(head));
    nodePtr newLast = LL_last(head);

    processTestResults("insertAtIndex - after last",
            last != newLast && last->value == newLast->value);
    LL_freeAll(&head);
}

