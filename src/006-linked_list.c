#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct node {
    int value;
    struct node *next;
};

void add(struct node **node, int value);
int get(struct node **node, int index);


int main() {
    struct node *list = NULL;
    add(&list, 1);
    add(&list, 2);
    assert(get(&list, 0) == 2);
    add(&list, 3);
    add(&list, 4);
    assert(get(&list, 3) == 1);
    assert(get(&list, 0) == 4);
    add(&list, 5);
    assert(get(&list, 0) == 5);

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
