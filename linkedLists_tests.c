#include "linkedLists.c"
#include <stdlib.h>

// Level 0
void LL_length_test(int count);
//void LL_last_test(int count);
void LL_reverse_test(int count);
void LL_ofIndex_test(int count);
void LL_indexOf_test(int count);
void LL_find_test(int count);
void LL_findBefore_test(int count);

// Level 1
void LL_push_test(int count);
void LL_pop_test(int count);
void LL_free_test(int count);
void LL_concat_test(int count);
void LL_lastN_test(int count);
void LL_toArray_test(int count);
void LL_split_test(int count);
void LL_freeAll_test(int count);
void LL_findAll_test(int count);

// Level 2
void LL_pushMany_test(int count);
void LL_popMany_test(int count);
void LL_freeMany_test(int count);
void LL_insertAtIndex_test(int count);
void LL_insertAfter_test(int count);

// Level 3
void LL_forEach_test(int count);
void forEach_callback(nodePtr* head, nodePtr n);
void forEach_validationCallback(nodePtr* head, nodePtr n);

// Diagnostics
void processTestResults(char* testName, int results);
int testResults = 1;
char randTestVal();
nodePtr newTestLL(int count);


int main(int argc, const char* argv[]) {
    int const testValue = argc > 1 ? atoi(argv[1]) : 9377;

    puts("\nTesting linked list functionality . . .\n");

// Level 0
    LL_length_test(testValue);
    //LL_last_test(testValue);
    LL_reverse_test(testValue);
    LL_ofIndex_test(testValue);
    LL_indexOf_test(testValue);
    LL_find_test(testValue);
    LL_findBefore_test(testValue);
// Level 1
    LL_push_test(testValue);
    LL_pop_test(testValue);
    LL_free_test(testValue);
    LL_concat_test(testValue);
    LL_lastN_test(testValue);
    LL_toArray_test(testValue);
    LL_split_test(testValue);
    LL_freeAll_test(testValue);
    LL_findAll_test(testValue);
// Level 2
    LL_pushMany_test(testValue);
    LL_popMany_test(testValue);
    LL_freeMany_test(testValue);
    LL_insertAfter_test(testValue);
    LL_insertAtIndex_test(testValue);
// Level 3
    LL_forEach_test(testValue);

// Diagnostics
    puts("");
    processTestResults("Pass ALL the tests", testResults);

    return 0;
}


// Level 0
void LL_length_test(int count) {
    nodePtr head = newTestLL(count);
    int i = 1;
    nodePtr n = head;
    while ((n = n->next))
        i++;
    processTestResults("length: head", LL_length(head) == i);
    processTestResults("length: NULL", LL_length(NULL) == 0);
    LL_freeAll(&head);
}
//void LL_last_test(int count) {
//
//}
void LL_reverse_test(int count) {
    nodePtr head = newTestLL(count), n, newHead;
    for (n = head, newHead = NULL; n; n = n->next) {
       if (n)
           LL_append(&newHead, n->value);
    }

    int results = 1;
    head = LL_reverse(head, NULL);
    results &= newHead->value == LL_last(head)->value;

    head = LL_reverse(head, NULL); // Reverse back to how it was before this function.
    nodePtr tempHead = head,
            tempNewHead = newHead;
    do
        results &= tempNewHead->value == tempHead->value;
    while ((tempNewHead = tempNewHead->next) && (tempHead = tempHead->next));

    processTestResults("reverse", results);
    LL_freeAll(&head);
}
void LL_ofIndex_test(int count) {
    int index = count / 2;
    nodePtr head = newTestLL(count),
            n = head;
    int i, elemsResults;
    for (i = 0, elemsResults = 1; i <= index; i++, n = n->next)
        elemsResults &= n == LL_ofIndex(head, i);
    processTestResults("ofIndex: elems", elemsResults);
    processTestResults("ofIndex: negative index", NULL == LL_ofIndex(head, -1));
    processTestResults("ofIndex: NULL head", NULL == LL_ofIndex(NULL, index));
    LL_freeAll(&head);
}
void LL_indexOf_test(int count) {
    int index = count / 2;
    nodePtr head = newTestLL(count),
        n = head;
    int i, results;
    for (i = 0, results = 1; i <= index ; i++, n = n->next)
        results &= i == LL_indexOf(head, n);
    processTestResults("indexOf: elems", results);
    processTestResults("indexOf: NULL elem", -1 == LL_indexOf(head, NULL));
    processTestResults("indexOf: NULL head", -1 == LL_indexOf(NULL, head->next));
    LL_freeAll(&head);
}
void LL_find_test(int count) {
    nodePtr head = newTestLL(count);
    nodePtr indexedN = LL_ofIndex(head, LL_length(head) / 2);
    LL_value_t indexedNValue = LL_findByValue(head, indexedN->value)->value;
    processTestResults("find: value in list", indexedNValue == indexedN->value);
    LL_free(&head, &indexedN);
    processTestResults("find: value not in list", LL_find(head, indexedN) == NULL);
    LL_freeAll(&head);
}
void LL_findBefore_test(int count) {
    nodePtr head = newTestLL(count);
    processTestResults("findBefore: head", LL_findBefore(head, head) == NULL);
    processTestResults("findBefore: elem", LL_findBefore(head, head->next->next) == head->next);
    LL_freeAll(&head);
}

// Level 1
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
    LL_value_t nVal = n->value;
    LL_value_t popVal = LL_pop(&head);

    processTestResults("pop", nVal == popVal);
    LL_freeAll(&head);
}
void LL_free_test(int count) {
    nodePtr head = newTestLL(count);

    LL_value_t headValue = head->value;
    LL_free(&head, &head);
    processTestResults("free: deallocate head", headValue != head->value);

    nodePtr n = LL_ofIndex(head, count / 2);
    LL_free(&head, &n);
    processTestResults("free: deallocate elem", LL_indexOf(head, n) == LL_length(head)-1);

    LL_freeAll(&head);
}
void LL_concat_test(int count) {
    nodePtr head = newTestLL(count);
    int i, len = LL_length(head);
    nodePtr n = head->next, newHead = NULL;
    LL_push(&newHead, head->value);
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

    int aResults = 1, bResults = 1;
    aResults &= head == firstNode && LL_last(head) == beforeMid;
    bResults &= backHalf == midNode && LL_last(backHalf) == lastNode;

    processTestResults("split - b && b", aResults && bResults);
    LL_freeAll(&head);
    LL_freeAll(&backHalf);

    head = newTestLL(17);
    LL_split(&head, &backHalf);
    processTestResults("split - odd:  [a] > [b]", LL_length(head) == 1+LL_length(backHalf));
    LL_freeAll(&head);
    LL_freeAll(&backHalf);

    head = newTestLL(18);
    LL_split(&head, &backHalf);
    processTestResults("split - even: [a] = [b]", LL_length(head) == LL_length(backHalf));
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

// Level 2
void LL_pushMany_test(num) {

}
void LL_popMany_test(int count) {
    nodePtr head = newTestLL(count);
    int index = count / 2;
    LL_value_t* lastCountValues = LL_toArray(LL_lastN(head, index));
    LL_value_t* poppedCountValues = LL_popMany(&head, index);

    int results, i;
    for (results = 1, i = 0; i < index; i++)
        results &= poppedCountValues[i] == lastCountValues[i];
    free(poppedCountValues);
    free(lastCountValues);

    processTestResults("popMany", results);
    LL_freeAll(&head);
}
void LL_freeMany_test(int count) {
    nodePtr head = newTestLL(count);
    nodePtr n = head->next;
    LL_freeMany(&head, &n, count / 2);
    processTestResults("freeMany", LL_find(head, n) == NULL);
    LL_freeAll(&head);
}
void LL_insertAfter_test(int count) {
    nodePtr head = newTestLL(count);
    int results = 1;
    results &= head->next->value != count;
    LL_value_t testV = randTestVal();
    LL_insertAfter(&head, testV);
    results &= head->next->value == testV;
    processTestResults("insertAfter", results);
}
void LL_insertAtIndex_test(int count) {
    nodePtr head = newTestLL(count);
    LL_insertAtIndex(&head, head->value, 0);
    processTestResults("insertAtIndex - before head", head->value == head->next->value);

    LL_value_t valueToFind = head->next->next->value; // A value several nodes into the list.
    nodePtr beforeInsert = LL_findAll(head, valueToFind);
    LL_insertAtIndex(&head, valueToFind, count / 2);
    nodePtr afterInsert = LL_findAll(head, valueToFind);
    processTestResults("insertAtIndex - between nodes", LL_length(beforeInsert)+1 == LL_length(afterInsert));
    LL_freeAll(&beforeInsert);
    LL_freeAll(&afterInsert);

    nodePtr last = LL_last(head);
    LL_insertAtIndex(&head, last->value, LL_length(head));
    nodePtr newLast = LL_last(head);
    processTestResults("insertAtIndex - after last", last != newLast && last->value == newLast->value);
    LL_freeAll(&head);
}

// Level 3
LL_value_t* testF_Values;
int forEach_validationCallback_results;
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

// Diagnostics
#define WHITE_CC "\e[0m"
#define GREEN_CC "\e[32m"
#define RED_CC   "\e[31m"
void processTestResults(char* testName, int results) {
    char* color = results ? GREEN_CC : RED_CC;
    char* text  = results ? "pass" : "fail";
    printf("\tTesting - %-30s: %s%s%s\n", testName, color, text, WHITE_CC);
    testResults &= results;
}
nodePtr newTestLL(int count) {
    nodePtr head = NULL;
    LL_push(&head, randTestVal());
    int i, j;
    for (i = 1, j = 0; i < count; i++, j++)
        LL_push(&head, randTestVal()); // Assuming LL_value_t is of type int.
    return head;
}
LL_value_t randTestVal() {
    // Produces a random char that satisfies [a-zA-Z].
    LL_value_t c = rand() % 52;
    c += c < 26 ? 'a' : 'A';
    return c;
}
