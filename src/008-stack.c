#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int value;
    struct node *next;
};

void push(struct node **node, int value);
int pop(struct node **node);

int main() {
    struct node *stack = NULL;
    push(&stack, 3);
    push(&stack, 5);
    assert(pop(&stack) == 5);
    push(&stack, 2);
    push(&stack, 7);
    assert(pop(&stack) == 7);
    assert(pop(&stack) == 2);
    assert(pop(&stack) == 3);

    printf("Success!");
    return 0;
}


void push(struct node **node, int value) {
    struct node *new_node = malloc(sizeof (struct node));
    new_node->value = value;
    new_node->next  = *node;

    *node = new_node;
}

int pop(struct node **node) {
    struct node *old = *node;
    int value = old->value;
    *node = old->next;
    free(old);
    return value;
}
