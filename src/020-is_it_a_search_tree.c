#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

struct node {
    int value;
    struct node *left, *right;
};

struct node *array_to_tree(int arr[], int n, int i);
bool is_search_tree(struct node *root, int min, int max);

int main() {
    int tree1[] = {10, 11, 12};
    struct node *node1 = array_to_tree(tree1, 3, 0);

    assert(is_search_tree(node1, INT_MIN, INT_MAX) == false);

    int tree2[] = {21, 11, 26, 5, 14, 23, 30, 2, 8, 13, 16, 0, 0, 0, 0};
    struct node *node2 = array_to_tree(tree2, 15, 0);

    assert(is_search_tree(node2, INT_MIN, INT_MAX) == true);

    printf("Success!");
    return 0;
}

bool is_search_tree(struct node *root, int min, int max) {
    if (root == NULL) return true;

    if (root->value > max || root->value < min) return false;

    return is_search_tree(root->left, min, root->value - 1)
        && is_search_tree(root->right, root->value + 1, max);
}

struct node *array_to_tree(int arr[], int n, int i) {
    if (i >= n || arr[i] == 0) return NULL;

    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = arr[i];
    new_node->left = array_to_tree(arr, n, i * 2 + 1);
    new_node->right = array_to_tree(arr, n, i * 2 + 2);

    return new_node;
}

