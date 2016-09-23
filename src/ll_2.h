#include "ll.h"


nodePtr     LL_pushMany      (nodePtr* headPtr, LL_value_t* values, int count);

LL_value_t* LL_popMany       (nodePtr* headPtr, int count);

void        LL_freeMany      (nodePtr* headPtr, nodePtr* startPtr, int count);

void        LL_insertAfter   (nodePtr* nPtr, LL_value_t value);

void        LL_insertAtIndex (nodePtr* headPtr, LL_value_t value, int index);
