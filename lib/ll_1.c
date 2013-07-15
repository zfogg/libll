
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

