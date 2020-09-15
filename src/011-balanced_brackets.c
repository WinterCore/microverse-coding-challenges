#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct node {
    char value;
    struct node *next;
};

void push(struct node **node, char value);
char pop(struct node **node);
bool empty(struct node **node);
char top(struct node **node);

int find_index(char *str, char c);
bool balanced_brackets(char *str);


int main() {
    assert(balanced_brackets("{}") == true);
    assert(balanced_brackets("(hello)[world]") == true);
    assert(balanced_brackets("[({}{}{})([])]") == true);

    assert(balanced_brackets("(hello") == false);
    assert(balanced_brackets("([)]") == false);
    assert(balanced_brackets(")(") == false);

    printf("Success!");

    return 0;
}

void push(struct node **node, char value) {
    struct node *new_node = malloc(sizeof (struct node));
    new_node->value = value;
    new_node->next  = *node;

    *node = new_node;
}

char top(struct node **node) {
    return (*node)->value;
}

char pop(struct node **node) {
    struct node *old = *node;
    char value = old->value;
    *node = old->next;
    free(old);
    return value;
}

bool empty(struct node **node) {
    return *node == NULL;
}

int find_index(char *str, char c) {
    int i = -1;
    while (str[++i])
        if (str[i] == c)
            return i;

    return -1;
}

bool balanced_brackets(char *str) {
    struct node *stack = NULL;
    char *opening = "([{",
         *closing = ")]}";
    while (*str) {
        int oi = find_index(opening, *str),
            ci = find_index(closing, *str);
        if (oi > -1) {
            push(&stack, opening[oi]);
        } else if (ci > -1) {
            if (empty(&stack) || find_index(opening, top(&stack)) != ci) return false;
            pop(&stack);
        }
        str += 1;
    }
    return empty(&stack);
}
