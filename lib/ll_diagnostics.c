#include <stdio.h>

#include "ll.h"


void LL_log(nodePtr head) {
    puts("");
    LL_forEach(&head, LL_logF);
    puts("");
}


// Log strings depend on the type of LL_value_t.
void LL_logF(nodePtr* headPtr, nodePtr n) {
    (void)(headPtr);
    printf(LL_LOGF_LOGSTRING, n, n->value);
}


void LL_logCompare(nodePtr head1, nodePtr head2) {
    puts("");
    do {
        LL_logCompareF(head1);
        LL_logCompareF(head2);
        puts("");
    } while ((head1 = head1->next) && (head2 = head2->next));
}


void LL_logCompareF(nodePtr n) {
    printf(LL_LOGCOMPARE_LOGSTRING, n, n->value);
}

