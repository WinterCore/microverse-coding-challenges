#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int value;
    struct node *next;
};

void add(struct node **node, int value);
int get(struct node **node, int index);
void add_at(struct node **node, int value, int index);
int delete_at(struct node **node, int index);


int main() {
    struct node *tree = NULL;
    add(&tree, 1);
    add(&tree, 3);
    add_at(&tree, 2, 1);
    assert(get(&tree, 0) == 3);
    assert(get(&tree, 1) == 2);
    assert(get(&tree, 2) == 1);
    assert(delete_at(&tree, 2) == 1);
    assert(delete_at(&tree, 0) == 3);

    printf("Success!\n");
    return 0;
}



void add(struct node **node, int value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next  = *node;

    *node = new_node;
}

int get(struct node **node, int index) {
    while (index-- > 0) node = &(*node)->next;
    return (*node)->value;
}

void add_at(struct node **node, int value, int index) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;

    while (index-- > 0) node = &(*node)->next;
    new_node->next = *node;
    *node = new_node;
}

int delete_at(struct node **node, int index) {
    while (index-- > 0) node = &(*node)->next;
    struct node *old = (*node);
    int value = (*node)->value;
    *node = (*node)->next;
    free(old);
    return value;
}
