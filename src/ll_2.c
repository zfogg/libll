#include "ll.h"


nodePtr LL_pushMany(nodePtr* headPtr, LL_value_t* values, int count) {
    nodePtr newHead = LL_push(headPtr, values[0]);
    int i;
    for (i = 1; i < count; i++)
        LL_push(&newHead, values[i]);
    return newHead;
}


LL_value_t* LL_popMany(nodePtr* headPtr, int count) {
    if (count >= LL_length(*headPtr)) {
        LL_value_t* values = LL_toArray(*headPtr);
        LL_freeAll(headPtr);
        return values;
    }
    else {
        int indexOfHeadToPop = LL_length(*headPtr) - count - 1; // -1 for zero-indexing.
        nodePtr headToPop = LL_ofIndex(*headPtr, indexOfHeadToPop);
        LL_value_t* values = LL_toArray(headToPop);
        LL_freeAll(&headToPop->next);
        return values;
    }
}


void LL_freeMany(nodePtr* headPtr, nodePtr* startPtr, int count) {
    if (count >= LL_length(*startPtr)) {
        nodePtr beforeStart = LL_findBefore(*headPtr, *startPtr);
        if (beforeStart)
            beforeStart->next = NULL;
        LL_freeAll(startPtr);
    }
    else {
        nodePtr end         = LL_ofIndex(*startPtr, count),
                n           = (*startPtr),
                beforeStart = LL_findBefore(*headPtr, *startPtr);
        while (n->next != end)
            n = LL_free(startPtr, &n);
        if (beforeStart->next)
            beforeStart->next = end;
    }
}


void LL_insertAfter(nodePtr* nPtr, LL_value_t value) {
    nodePtr newN = NULL;
    LL_push(&newN, value);
    newN->next = (*nPtr)->next;
    (*nPtr)->next = newN;
}


void LL_insertAtIndex(nodePtr* head, LL_value_t value, int index) {
    nodePtr n = LL_findBefore(*head, LL_ofIndex(*head, index));
    nodePtr newN = NULL;
    LL_push(&newN, value);
    if (n) {
        newN->next = n->next;
        n->next = newN;
    }
    else {
        newN->next = *head;
        *head = newN;
    }
}

