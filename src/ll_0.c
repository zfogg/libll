#include "ll.h"


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

