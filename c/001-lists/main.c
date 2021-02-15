#include <stdio.h>

#include "linked-list.h"

int main() {
    struct Node *node = NULL;
    ll_add(&node, 3);
    ll_add(&node, 5);
    printf("=> %d", ll_get(&node, 1));

    return 0;
}
