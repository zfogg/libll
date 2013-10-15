#ifndef ll_h__
#define ll_h__


#ifndef NULL
#define NULL (0)
#endif

#define LL_value_t char


typedef struct node {
    LL_value_t value;
    struct node* next;
} node;
typedef struct node* nodePtr;


// Level 0
int         LL_length        (nodePtr head);

nodePtr     LL_last          (nodePtr head);

nodePtr     LL_reverse       (nodePtr head, nodePtr prev);

nodePtr     LL_ofIndex       (nodePtr head, int index);

int         LL_indexOf       (nodePtr head, nodePtr n);

nodePtr     LL_findByValue   (nodePtr head, LL_value_t value);

nodePtr     LL_find          (nodePtr head, nodePtr n);

nodePtr     LL_findBefore    (nodePtr head, nodePtr n);


// Level 1

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


// Level 2

nodePtr     LL_pushMany      (nodePtr* headPtr, LL_value_t* values, int count);

LL_value_t* LL_popMany       (nodePtr* headPtr, int count);

void        LL_freeMany      (nodePtr* headPtr, nodePtr* startPtr, int count);

void        LL_insertAfter   (nodePtr* nPtr, LL_value_t value);

void        LL_insertAtIndex (nodePtr* headPtr, LL_value_t value, int index);


// Level 3

void        LL_forEach       (nodePtr* headPtr, void                            ( *callBack) ( nodePtr*, nodePtr));

void        LL_forEachRef    (nodePtr* headPtr, void                            ( *callBack) ( nodePtr*, nodePtr*));


// Diagnostics

#define LL_LOGF_LOGSTRING       "n:[%p]->value[%c]\n"

#define LL_LOGCOMPARE_LOGSTRING "n:[%p]->value[%c]\t"

void        LL_log           (nodePtr head);

void        LL_logF          (nodePtr* headPtr, nodePtr n);

void        LL_logCompare    (nodePtr head1, nodePtr head2);

void        LL_logCompareF   (nodePtr n);


#endif // ll_h__

