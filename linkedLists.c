#include <stdlib.h>
#include <stdio.h>

#define LL_value_t char
#define LL_value_t_TRUE  0x01
#define LL_value_t_FALSE 0x00

typedef struct node {
    LL_value_t value;
    struct node* next;
} node;
typedef struct node* nodePtr;

// Level n may use functions from Level x, where x =< n.
// Level 0
int         LL_length(nodePtr head);
nodePtr     LL_last(nodePtr head);
nodePtr     LL_reverse(nodePtr head, nodePtr prev);

nodePtr     LL_ofIndex(nodePtr head, int index);
int         LL_indexOf(nodePtr head, nodePtr n);

nodePtr     LL_findByValue(nodePtr head, LL_value_t value);
nodePtr     LL_find(nodePtr head, nodePtr n);
nodePtr     LL_findBefore(nodePtr head, nodePtr n);

// Level 1
nodePtr     LL_push(nodePtr* headPtr, LL_value_t value);
nodePtr     LL_append(nodePtr* headPtr, LL_value_t value);
LL_value_t  LL_pop(nodePtr* headPtr);
nodePtr     LL_free(nodePtr* headPtr, nodePtr* nPtr);

void        LL_concat(nodePtr* headPtr1, nodePtr* headPtr2);
nodePtr     LL_lastN(nodePtr head, int count);
LL_value_t* LL_toArray(nodePtr head);
void        LL_split(nodePtr* headPtr, nodePtr* backHalfPtr);

void        LL_freeAll(nodePtr* headPtr);
nodePtr     LL_findAll(nodePtr head, LL_value_t value);

nodePtr     LL_unlink(nodePtr* headPtr, nodePtr* n);
void        LL_moveNode(nodePtr *head1, nodePtr* head2);

// Level 2
nodePtr     LL_pushMany(nodePtr* headPtr, LL_value_t* values, int count);
LL_value_t* LL_popMany(nodePtr* headPtr, int count);
void        LL_freeMany(nodePtr* headPtr, nodePtr* startPtr, int count);

void        LL_insertAfter(nodePtr* nPtr, LL_value_t value);
void        LL_insertAtIndex(nodePtr* headPtr, LL_value_t value, int index);

// Level 3
void        LL_forEach(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr));
void        LL_forEachRef(nodePtr* headPtr, void (*callBack)(nodePtr*, nodePtr*));

// Diagnostics
void        LL_log(nodePtr head);
void        LL_logF(nodePtr* headPtr, nodePtr n);
void        LL_logCompare(nodePtr head1, nodePtr head2);
void        LL_logCompareF(nodePtr n);


// Level 0
int LL_length(nodePtr head) {
    return head ? 1 + LL_length(head->next) : 0;
}
nodePtr LL_last(nodePtr head) {
    return head->next ? LL_last(head->next) : head;
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
nodePtr LL_findByValue(nodePtr head, LL_value_t value) {
    while(head && head->value != value)
        head = head->next;
    return head;
}
nodePtr LL_find(nodePtr head, nodePtr n) {
    while(head && head != n)
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
nodePtr LL_newNode(LL_value_t value) {
    nodePtr n = malloc(sizeof(node));
    n->value = value;
    return n;
}
nodePtr LL_push(nodePtr* headPtr, LL_value_t value) {
    nodePtr n = LL_newNode(value);
    n->next = *headPtr ? *headPtr : NULL;
    *headPtr = n;
    return n;
}
nodePtr LL_append(nodePtr* headPtr, LL_value_t value) {
    nodePtr n = LL_newNode(value);
    n->next = NULL;
    if (*headPtr)
        LL_last(*headPtr)->next = n;
    else
        *headPtr = n;
    return n;
}
LL_value_t LL_pop(nodePtr* headPtr) {
    nodePtr n = LL_last(*headPtr);
    LL_value_t results = n->value;
    LL_free(headPtr, &n);
    return results;
}
nodePtr LL_free(nodePtr* headPtr, nodePtr* n) {
    nodePtr nNext = (*n)->next;
    free( LL_unlink(headPtr, n) );
    if (*headPtr == *n && headPtr != n)
        *n = NULL;
    return nNext;
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
LL_value_t* LL_toArray(nodePtr head) {
    nodePtr n;
    int len = LL_length(head), i;
    LL_value_t* values = malloc(len * sizeof(LL_value_t));
    for (n = head, i = 0; n->next; n = n->next, i++)
        values[i] = n->value;
    return values;
}
void LL_split(nodePtr* headPtr, nodePtr* backHalfPtr) {
    nodePtr head = *headPtr;
    int len = LL_length(head) / 2;
    len -= (len%2)-1; // If len is odd, the first half gets the remainder node.
    nodePtr beforeHalf = LL_findBefore(head, LL_ofIndex(head, len));
    *backHalfPtr = beforeHalf->next;
    beforeHalf->next = NULL;
}
void LL_freeAll(nodePtr* headPtr) {
    nodePtr n = *headPtr;
    do
        LL_free(headPtr, &n);
    while ((n = n->next));
    *headPtr = NULL;
}
nodePtr LL_findAll(nodePtr head, LL_value_t value) {
    nodePtr n       = head,
            newHead = NULL;
    do
        if (n->value == value)
            LL_push(&newHead, value);
    while ((n = n->next));
    return newHead;
}
nodePtr LL_unlink(nodePtr* headPtr, nodePtr* nPtr) {
    nodePtr n = *nPtr;
    if (*headPtr == n)
        *headPtr = n->next;
    else
        LL_findBefore(*headPtr, n)->next = n->next;
    n->next = NULL;
    return n;
}
void LL_moveNode(nodePtr *head1, nodePtr* head2) {
    nodePtr lastNode = LL_last(*head1),
            n        = LL_unlink(head1, &lastNode);
    LL_last(*head2)->next = n;
}

// Level 2
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

// Level 3
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

// Diagnostics
void LL_log(nodePtr head) {
    puts("");
    LL_forEach(&head, LL_logF);
    puts("");
}
// Log strings depend on the type of LL_value_t.
char* const LL_logF_logString       = "n:[%p]->value[%c]\n";
char* const LL_logCompare_logString = "n:[%p]->value[%c]\t";
void LL_logF(nodePtr* headPtr, nodePtr n) {
    printf(LL_logF_logString, n, n->value);
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
    printf(LL_logCompare_logString, n, n->value);
}
