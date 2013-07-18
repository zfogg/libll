
void LL_push_test(int count) {
    nodePtr head = NULL;
    LL_push(&head, 0);
    processTestResults("push: new head", head->value == 0);

    int i, j;
    for (i = 1, j = 0; i < count; i++, j++)
        LL_push(&head, i);

    nodePtr n = head;
    while ((n = n->next))
        j--; // confirm each node by counting back down to zero.

    processTestResults("push: new elements", i - count == j);
    LL_freeAll(&head);
}


void LL_pop_test(int count) {
    nodePtr head = newTestLL(count),
            n    = head;

    while (n->next)
        n = n->next;

    LL_value_t nVal   = n->value,
               popVal = LL_pop(&head);

    processTestResults("pop", nVal == popVal);
    LL_freeAll(&head);
}


void LL_free_test(int count) {
    nodePtr head = newTestLL(count);

    LL_value_t headValue = head->value;
    LL_free(&head, &head);
    processTestResults("free: deallocate head",
            headValue != head->value);

    nodePtr n = LL_ofIndex(head, count / 2);
    LL_free(&head, &n);
    processTestResults("free: deallocate elem",
            LL_indexOf(head, n) == LL_length(head)-1);

    LL_freeAll(&head);
}


void LL_concat_test(int count) {
    nodePtr head = newTestLL(count),
            n    = head->next, newHead = NULL;

    LL_push(&newHead, head->value);

    int i,len = LL_length(head);
    for (i = len-1; i > 0; n = n->next, i--)
        LL_push(&newHead, n->value);

    LL_concat(&head, &newHead);
    processTestResults("concat", LL_length(head) == len*2);

    free(LL_popMany(&head, LL_length(newHead)));
    LL_freeAll(&head);
}


void LL_lastN_test(int count) {
    nodePtr head = newTestLL(count),
            half = LL_lastN(head, count / 2);

    int halfLen = LL_length(head) / 2;
    halfLen += halfLen % 2 ? 0 : 1;

    processTestResults("lastN - half", LL_length(half) == halfLen);
    LL_freeAll(&head);
}


void LL_toArray_test(int count) {
    nodePtr head = newTestLL(count),
            n    = head;
    LL_value_t values[count];

    int i = 0;
    do
        values[i++] = n->value;
    while ((n = n->next));

    int results = 1;
    for (i = 0, n = head; i < count; i++, n = n->next)
        results &= values[i] == n->value;

    processTestResults("toArray", results);
    LL_freeAll(&head);
}


void LL_split_test(int count) {
    nodePtr head = newTestLL(count),
            backHalf;

    int len = LL_length(head);
    len += len % 2 ? 1 : 0;
    len /= 2;

    nodePtr firstNode = head,
            midNode   = LL_ofIndex(head, len),
            beforeMid = LL_findBefore(head, midNode),
            lastNode  = LL_last(head);

    LL_split(&head, &backHalf);

    int aResults = 1,
        bResults = 1;
    aResults &= head == firstNode && LL_last(head) == beforeMid;
    bResults &= backHalf == midNode && LL_last(backHalf) == lastNode;

    processTestResults("split - b && b", aResults && bResults);
    LL_freeAll(&head);
    LL_freeAll(&backHalf);

    head = newTestLL(17);
    LL_split(&head, &backHalf);
    processTestResults("split - odd:  [a] > [b]",
            LL_length(head) == 1+LL_length(backHalf));
    LL_freeAll(&head);
    LL_freeAll(&backHalf);

    head = newTestLL(18);
    LL_split(&head, &backHalf);
    processTestResults("split - even: [a] = [b]",
            LL_length(head) == LL_length(backHalf));
    LL_freeAll(&head);
    LL_freeAll(&backHalf);
}


void LL_freeAll_test(int count) {
    nodePtr head = newTestLL(count);
    LL_freeAll(&head);
    processTestResults("freeAll", head == NULL);
}


void LL_findAll_test(int count) {
    nodePtr head = newTestLL(count);
    LL_value_t value = LL_ofIndex(head, count / 2)->value;
    nodePtr newHead = LL_findAll(head, value);

    processTestResults("findAll", newHead->value == value);
    LL_freeAll(&newHead);
    LL_freeAll(&head);
}

