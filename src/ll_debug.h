#define LL_LOGF_LOGSTRING       "n:[%p]->value[%c]\n"

#define LL_LOGCOMPARE_LOGSTRING "n:[%p]->value[%c]\t"

void        LL_log           (nodePtr head);

void        LL_logF          (nodePtr* headPtr, nodePtr n);

void        LL_logCompare    (nodePtr head1, nodePtr head2);

void        LL_logCompareF   (nodePtr n);
