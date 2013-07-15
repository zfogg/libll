
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

