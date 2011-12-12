#include <stdlib.h>
#include <stdio.h>

typedef struct node node;
typedef struct node* nodePtr;

// Level n may use functions from Level x, where x =< n.
// Level 0
int     LL_length(nodePtr head);
nodePtr LL_last(nodePtr head);
nodePtr LL_reverse(nodePtr head, nodePtr prev);

nodePtr LL_ofIndex(nodePtr head, int i);
int     LL_indexOf(nodePtr head, nodePtr n);

nodePtr LL_find(nodePtr head, int value);
nodePtr LL_findBefore(nodePtr head, nodePtr n);

// Level 1
nodePtr LL_push(nodePtr* headPtr, int value);
int     LL_pop(nodePtr* headPtr);
void    LL_free(nodePtr* headPtr, nodePtr* nPtr);

void    LL_concat(nodePtr* headPtr1, nodePtr* headPtr2);
nodePtr LL_lastN(nodePtr head, int count);
int*    LL_toArray(nodePtr head);
void    LL_split(nodePtr* headPtr, nodePtr* backHalfPtr);

void    LL_freeAll(nodePtr* headPtr);
nodePtr LL_findAll(nodePtr head, int value);

// Level 2
nodePtr LL_pushMany(nodePtr* headPtr, int* values, int count);
int*    LL_popMany(nodePtr* headPtr, int count);
void    LL_freeMany(nodePtr* headPtr, nodePtr* startPtr, int count);

void    LL_insertAfter(nodePtr* nPtr, int value);
void    LL_insertAtIndex(nodePtr* headPtr, int value, int index);

// Level 3
void    LL_forEach(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr));
void    LL_forEachRef(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr*));

// Diagnostics
void LL_log(nodePtr head);
void LL_logF(nodePtr* headPtr, nodePtr n);
void LL_logCompare(nodePtr head1, nodePtr head2);
void LL_logCompareF(nodePtr n);


struct node {
    int value;
    nodePtr next;
};

// Level 0
int LL_length(nodePtr head) {
    return head ? 1 + LL_length(head->next) : 0;
}
nodePtr LL_last(nodePtr n) {
    while (n->next)
        n = n->next;
    return n;
}
nodePtr LL_ofIndex(nodePtr head, int index) {
    if (head && index >= 0)
        return !index ? head : LL_ofIndex(head->next, index-1);
    else
        return NULL;
}
int LL_indexOf(nodePtr head, nodePtr n) {
    if (head && n)
        return head == n ? 0 : 1 + LL_indexOf(head->next, n);
    else
        return -1;
}
nodePtr LL_find(nodePtr head, int value) {
    while(head && head->value != value)
        head = head->next;
    return head;
}
nodePtr LL_findBefore(nodePtr head, nodePtr n) {
    nodePtr i = NULL;
    if (n != head) {
        i = head;
        while (i && i->next != n)
            i = i->next;
    }
    return i;
}
nodePtr LL_reverse(nodePtr head, nodePtr prev) {
    if (head->next == NULL) {
        head->next = prev;
        return head;
    }
    else {
        nodePtr n = LL_reverse(head->next, head);
        head->next = prev;
        return n;
    }
}

// Level 1
nodePtr LL_push(nodePtr* headPtr, int value) {
    nodePtr n = malloc(sizeof(node));

    n->next = NULL;
    n->value = value;

    if (*headPtr)
        LL_last(*headPtr)->next = n;
    else
        *headPtr = n;

    return n;
}
int LL_pop(nodePtr* headPtr) {
    nodePtr n = LL_last(*headPtr);
    int results = n->value;
    LL_free(headPtr, &n);
    return results;
}
void LL_free(nodePtr* headPtr, nodePtr* nPtr) {
    nodePtr i = *headPtr, n = *nPtr;
    if (i == n)
        *headPtr = i->next;
    else {
        while (i && i->next != n) // Find n-1.
            i = i->next;
        i->next = n->next; // Link n-1 to n+1.
    }
    free(n);
}
void LL_concat(nodePtr* headPtr1, nodePtr* headPtr2) {
    LL_last(*headPtr1)->next = *headPtr2;
}
nodePtr LL_lastN(nodePtr head, int count) {
    nodePtr n;
    for (n = head; n->next; n = n->next)
        if (n == LL_ofIndex(head, count))
            head = head->next;
    return head;
}
int* LL_toArray(nodePtr head) {
    nodePtr n;
    int len = LL_length(head);
    int* values = malloc(len * sizeof(int));
    int i;
    for (n = head, i = 0; n->next; n = n->next, i++)
        values[i] = n->value;
    return values;
}
void LL_split(nodePtr* headPtr, nodePtr* backHalfPtr) {
    nodePtr head = *headPtr;
    int len = LL_length(head);
    len += len % 2 ? 1 : 0;
    len /= 2;
    nodePtr beforeHalf = LL_findBefore(head, LL_ofIndex(head, len));
    *backHalfPtr = beforeHalf->next;
    beforeHalf->next = NULL;
}
void LL_freeAll(nodePtr* headPtr) {
    nodePtr n = *headPtr;
    do
        LL_free(headPtr, &n);
    while (n = n->next);
    *headPtr = NULL;
}
nodePtr LL_findAll(nodePtr head, int value) {
    nodePtr n = head,
            newHead = NULL;
    do
        if (n->value == value)
            LL_push(&newHead, value);
    while (n = n->next);
    return newHead;
}

// Level 2
nodePtr LL_pushMany(nodePtr* headPtr, int* values, int count) {
    nodePtr newHead = LL_push(headPtr, values[0]);
    int i;
    for (i = 1; i < count; i++)
        LL_push(&newHead, values[i]);
    return newHead;
}
int* LL_popMany(nodePtr* headPtr, int count) {
    if (count >= LL_length(*headPtr)) {
        int* values = LL_toArray(*headPtr);
        LL_freeAll(headPtr);
        return values;
    }
    else {
        int i;
        nodePtr headToPop, temp = *headPtr;
        for (i = 0, headToPop = *headPtr; temp->next; temp = temp->next)
            if (temp == LL_ofIndex(headToPop, count))
                headToPop = headToPop->next;

        int* values = LL_toArray(headToPop);
        LL_freeAll(&headToPop->next);
        return values;
    }
}
void LL_freeMany(nodePtr* headPtr, nodePtr* startPtr, int count) {
    nodePtr end = LL_ofIndex(*startPtr, count),
            n = *startPtr,
            beforeStart = LL_findBefore(*headPtr, *startPtr);
    do
        LL_free(startPtr, &n);
    while (end != (n = n->next));
    if (beforeStart->next) {
        beforeStart->next = end->next;
        LL_free(startPtr, startPtr);
    }
}
void LL_insertAfter(nodePtr* nPtr, int value) {
    nodePtr newN = NULL;
    LL_push(&newN, value);
    newN->next = (*nPtr)->next;
    (*nPtr)->next = newN;
}
void LL_insertAtIndex(nodePtr* head, int value, int index) {
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

// Level 3
void LL_forEach(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr)) {
    nodePtr n = *headPtr;
    do
        callBack(headPtr, n);
    while (n = n->next);
}
void LL_forEachRef(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr*)) {
    nodePtr* n = headPtr;
    do
        callBack(headPtr, n);
    while (n = &(*n)->next);
}

// Diagnostics
void LL_log(nodePtr head) {
    LL_forEach(&head, LL_logF);
}
void LL_logF(nodePtr* headPtr, nodePtr n) {
    printf("n:[%p]->value[%d]\n", n, n->value);
}
char* LL_logCompare_logString = "n:[%p]->value[%d]\t";
void LL_logCompare(nodePtr head1, nodePtr head2) {
    do {
        LL_logCompareF(head1);
        LL_logCompareF(head2);
        puts("");
    } while ((head1 = head1->next) && (head2 = head2->next));
}
void LL_logCompareF(nodePtr n) {
    printf("n:[%p]->value[%d]\t", n, n->value);
}
