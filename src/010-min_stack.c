#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct node {
    int value;
    struct node *next;
};

struct min_stack {
    struct node *stack;
    struct node *min_stack;
};

void push(struct min_stack *stack, int value);
int pop(struct min_stack *stack);
int min(struct min_stack *stack);
bool empty(struct min_stack *stack);

int main() {
    struct min_stack *stack = malloc(sizeof(struct min_stack));
    push(stack, 3);
    push(stack, 5);
    assert(min(stack) == 3);
    assert(pop(stack) == 5);
    push(stack, 7);
    assert(min(stack) == 3);
    push(stack, 2);
    assert(min(stack) == 2);
    assert(pop(stack) == 2);
    assert(min(stack) == 3);
    push(stack, 2);
    push(stack, 2);
    assert(min(stack) == 2);
    assert(pop(stack) == 2);
    assert(pop(stack) == 2);
    assert(min(stack) == 3);

    printf("Success!");
    return 0;
}


void push(struct min_stack *stack, int value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = stack->stack;
    stack->stack = new_node;
    if (empty(stack) || min(stack) >= value) {
        struct node *new_min_node = malloc(sizeof(struct node));
        new_min_node->value = value;
        new_min_node->next = stack->min_stack;
        stack->min_stack = new_min_node;
    }
}

int pop(struct min_stack *stack) {
    int value = stack->stack->value;
    struct node *old_node = stack->stack;
    stack->stack = old_node->next;
    free(old_node);
    if (value == min(stack)) {
        struct node *old_min_node = stack->min_stack;
        stack->min_stack = old_min_node->next;
        free(old_min_node);
    }
    return value;
}

int min(struct min_stack *stack) {
    return stack->min_stack->value;
}

bool empty(struct min_stack *stack) {
    return !stack->min_stack;
}
