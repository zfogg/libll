#include "ll.h"


void        LL_forEach       (nodePtr* headPtr, void                            ( *callBack) ( nodePtr*, nodePtr));

void        LL_forEachRef    (nodePtr* headPtr, void                            ( *callBack) ( nodePtr*, nodePtr*));
