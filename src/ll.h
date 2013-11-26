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


#endif // ll_h__
