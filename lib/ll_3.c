#include "ll.h"


void LL_forEach(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr)) {
    nodePtr n = *headPtr;
    do
        callBack(headPtr, n);
    while ((n = n->next));
}


void LL_forEachRef(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr*)) {
    nodePtr* n = headPtr;
    do
        callBack(headPtr, n);
    while ((n = &(*n)->next));
}

