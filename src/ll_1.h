#include "ll.h"


nodePtr     LL_push          (nodePtr* headPtr, LL_value_t value);

nodePtr     LL_append        (nodePtr* headPtr, LL_value_t value);

LL_value_t  LL_pop           (nodePtr* headPtr);

nodePtr     LL_free          (nodePtr* headPtr, nodePtr* nPtr);

void        LL_concat        (nodePtr* headPtr1, nodePtr* headPtr2);

nodePtr     LL_lastN         (nodePtr head, int count);

LL_value_t* LL_toArray       (nodePtr head);

void        LL_split         (nodePtr* headPtr, nodePtr* backHalfPtr);

void        LL_freeAll       (nodePtr* headPtr);

nodePtr     LL_findAll       (nodePtr head, LL_value_t value);

nodePtr     LL_unlink        (nodePtr* headPtr, nodePtr* n);

void        LL_moveNode      (nodePtr *head1, nodePtr* head2);
