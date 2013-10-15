#include "../lib/ll.h"
#include "ll_tests.h"


void LL_length_test(int count) {
    nodePtr head = newTestLL(count);

    int i = 1;
    nodePtr n = head;
    while ((n = n->next))
        i++;

    processTestResults("length: head", LL_length(head) == i);
    processTestResults("length: NULL", LL_length(NULL) == 0);

    LL_freeAll(&head);
}


void LL_last_test(int count) {
  (void)(count);
}


void LL_reverse_test(int count) {
    nodePtr head = newTestLL(count), n, newHead;
    for (n = head, newHead = NULL; n; n = n->next) {
        if (n)
            LL_append(&newHead, n->value);
    }

    int results = 1;
    head = LL_reverse(head, NULL);
    results &= newHead->value == LL_last(head)->value;

    // Reverse back to how it was before this function.
    head = LL_reverse(head, NULL);
    nodePtr tempHead = head,
            tempNewHead = newHead;
    do
        results &= tempNewHead->value == tempHead->value;
    while ((tempNewHead = tempNewHead->next) && (tempHead = tempHead->next));

    processTestResults("reverse", results);
    LL_freeAll(&head);
}


void LL_ofIndex_test(int count) {
    int index = count / 2;
    nodePtr head = newTestLL(count),
            n = head;

    int i, elemsResults;
    for (i = 0, elemsResults = 1; i <= index; i++, n = n->next)
        elemsResults &= n == LL_ofIndex(head, i);

    processTestResults("ofIndex: elems", elemsResults);
    processTestResults("ofIndex: negative index",
            NULL == LL_ofIndex(head, -1));
    processTestResults("ofIndex: NULL head",
            NULL == LL_ofIndex(NULL, index));

    LL_freeAll(&head);
}


void LL_indexOf_test(int count) {
    int index = count / 2;
    nodePtr head = newTestLL(count),
            n = head;

    int i, results;
    for (i = 0, results = 1; i <= index ; i++, n = n->next)
        results &= i == LL_indexOf(head, n);

    processTestResults("indexOf: elems", results);
    processTestResults("indexOf: NULL elem",
            -1 == LL_indexOf(head, NULL));
    processTestResults("indexOf: NULL head",
            -1 == LL_indexOf(NULL, head->next));

    LL_freeAll(&head);
}


void LL_find_test(int count) {
    nodePtr head     = newTestLL(count),
            indexedN = LL_ofIndex(head, LL_length(head) / 2);

    LL_value_t indexedNValue = LL_findByValue(head, indexedN->value)->value;

    processTestResults("find: value in list",
            indexedNValue == indexedN->value);
    LL_free(&head, &indexedN);

    processTestResults("find: value not in list",
            LL_find(head, indexedN) == NULL);
    LL_freeAll(&head);
}


void LL_findBefore_test(int count) {
    nodePtr head = newTestLL(count);

    processTestResults("findBefore: head",
            LL_findBefore(head, head) == NULL);
    processTestResults("findBefore: elem",
            LL_findBefore(head, head->next->next) == head->next);

    LL_freeAll(&head);
}

