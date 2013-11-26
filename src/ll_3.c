#include "ll.h"
#include "ll_0.h"
#include "ll_1.h"
#include "ll_2.h"
#include "ll_3.h"


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

