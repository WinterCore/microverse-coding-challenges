#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct node {
    int value;
    struct node *next;
};

void push(struct node **node, int c);
int pop(struct node **node);
int top(struct node **node);
int get(struct node **node, int index);


int main() {
    struct node *stack = NULL;
    push(&stack, 5);
    push(&stack, 4);
    assert(top(&stack) == 4);
    assert(pop(&stack) == 4);
    assert(top(&stack) == 5);
    push(&stack, 2);
    push(&stack, 1);
    assert(get(&stack, 0) == 1);
    assert(get(&stack, 2) == 5);

    printf("Success!");
    return 0;
}


void push(struct node **node, int c) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = c;
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    if (*node) new_node->next = *node;
    *node = new_node;
}

int get(struct node **node, int index) {
    struct node *current = *node;
    while (index-- > 0) current = current->next;
    return current->value;
}

int pop(struct node **node) {
    if (*node == NULL) {
        fprintf(stderr, "The stack is empty!");
        exit(EXIT_FAILURE);
    }
    char value = (*node)->value;
    struct node *old = *node;
    *node = old->next;
    free(old);
    return value;
}

int top(struct node **node) {
    if (*node == NULL) {
        fprintf(stderr, "The stack is empty!");
        exit(EXIT_FAILURE);
    }
    return (*node)->value;
}
