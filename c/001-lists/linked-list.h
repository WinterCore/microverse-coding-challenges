#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

void ll_add(struct Node **node, int index);
int ll_get(struct Node **node, int index);

#endif
