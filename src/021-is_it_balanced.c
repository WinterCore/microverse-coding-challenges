#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


struct node {
    int value;
    struct node *left, *right;
    int height; // Store height to increase performance
};

struct node *array_to_tree(int arr[], int n, int i);
int height(struct node *node);
int max(int a, int b);
bool is_balanced(struct node *root);

int main() {
    int a[] = {1, 2, 0, 3, 4, 0, 0};
    int b[] = {1, 2, 3, 4, 5, 6, 7};
    struct node *treeA = array_to_tree(a, sizeof(a) / sizeof(a[0]), 0);
    struct node *treeB = array_to_tree(b, sizeof(b) / sizeof(b[0]), 0);

    assert(is_balanced(treeA) == false);
    assert(is_balanced(treeB) == true);

    printf("Success!");
    return 0;
}


bool is_balanced(struct node *root) {
    if (root == NULL) return true;

    bool a1 = abs(height(root->left) - height(root->right)) < 2,
         a2 = is_balanced(root->left),
         a3 = is_balanced(root->right);

    return a1 && a2 && a3;
}

int height(struct node *node) {
    if (node == NULL) return 0;

    return node->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct node *array_to_tree(int arr[], int n, int i) {
    if (i >= n || arr[i] == 0) return NULL;

    struct node *new_node = malloc(sizeof(struct node));
    new_node->value  = arr[i];
    new_node->left   = array_to_tree(arr, n, i * 2 + 1);
    new_node->right  = array_to_tree(arr, n, i * 2 + 2);
    new_node->height = max(height(new_node->left), height(new_node->right)) + 1;

    return new_node;
}

