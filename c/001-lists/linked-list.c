#include <stdlib.h>
#include "linked-list.h"

static struct Node *ll_get_node(struct Node *node, int index) {
    while (index > 0 && node != NULL) {
        node = node->next;
        index -= 1;
    }
    return node;
}

void ll_add(struct Node **node, int value) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    struct Node *curr = *node;
    if (curr == NULL) {
        *node = new_node;
        return;
    }

    while (curr->next)
        curr = curr->next;
    curr->next = new_node;
}

int ll_get(struct Node **node, int index) {
    struct Node *target = ll_get_node(*node, index);
    return target == NULL ? -1 : target->value;
}
