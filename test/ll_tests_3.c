
void LL_forEach_test(int count) {
    nodePtr head = newTestLL(count),
            n    = head;

    int i, len = LL_length(head);
    testF_Values = malloc(len * sizeof(LL_value_t));
    for (i = 0; i < len; i++, n = n->next)
        testF_Values[i] = n->value;

    LL_forEach(&head, forEach_callback);
    forEach_validationCallback_results = 1;
    LL_forEach(&head, forEach_validationCallback);

    free(testF_Values);
    testF_Values = NULL;

    processTestResults("forEach", forEach_validationCallback_results);
    LL_freeAll(&head);
}


void forEach_callback(nodePtr* head, nodePtr n) {
    n->value *= 2;
}


int testF2_i = 0;

void forEach_validationCallback(nodePtr* head, nodePtr n) {
    nodePtr testN = NULL;
    LL_push(&testN, testF_Values[testF2_i++]);

    forEach_callback(NULL, testN);
    forEach_validationCallback_results &= testN->value == n->value;

    LL_free(&testN, &testN);
}

