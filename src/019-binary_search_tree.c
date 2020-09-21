#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int value;
    struct node *left, *right;
};

void in_order(struct node *node, int *arr, int *i);
void push(struct node **node, int value);

int main() {
    // Test case 1
    int a[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    struct node *root1 = NULL;
    for (int i = sizeof(a) / sizeof(a[0]) - 1; i >= 0; i -= 1) {
        push(&root1, a[i]);
    }

    int actual1[9];
    int expected1[9] = {1, 3, 4, 6, 7, 8, 10, 13, 14};
    int j = 0;
    in_order(root1, actual1, &j);
    for (int i = sizeof(expected1) / sizeof(expected1[i]) - 1; i >= 0; i -= 1)
        assert(expected1[i] == actual1[i]);

    // Test case 2
    int b[] = {100, 200, 700, 600, 500, 400, 300, 0, 1000};
    struct node *root2 = NULL;
    for (int i = sizeof(b) / sizeof(b[0]) - 1; i >= 0; i -= 1) {
        push(&root2, b[i]);
    }
    int actual2[9];
    int expected2[9] = {0, 100, 200, 300, 400, 500, 600, 700, 1000};
    j = 0;
    in_order(root2, actual2, &j);
    for (int i = sizeof(expected2) / sizeof(expected2[i]) - 1; i >= 0; i -= 1)
        assert(expected2[i] == actual2[i]);

    printf("Success!");
    return 0;
}

void push(struct node **node, int value) {
    if (*node == NULL) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->value = value;
        *node = new_node;
    } else {
        if ((*node)->value < value) {
            push(&(*node)->right, value);
        } else {
            push(&(*node)->left, value);
        }
    }
}

void in_order(struct node *node, int *arr, int *i) {
    if (node == NULL) return;

    in_order(node->left, arr, i);
    arr[*i] = node->value;
    *i += 1;
    in_order(node->right, arr, i);
}