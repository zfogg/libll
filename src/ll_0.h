int         LL_length        (nodePtr head);

nodePtr     LL_last          (nodePtr head);

nodePtr     LL_reverse       (nodePtr head, nodePtr prev);

nodePtr     LL_ofIndex       (nodePtr head, int index);

int         LL_indexOf       (nodePtr head, nodePtr n);

nodePtr     LL_findByValue   (nodePtr head, LL_value_t value);

nodePtr     LL_find          (nodePtr head, nodePtr n);

nodePtr     LL_findBefore    (nodePtr head, nodePtr n);
