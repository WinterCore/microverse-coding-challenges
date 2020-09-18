#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int value;
    struct node *left, *right;
};

struct node *array_to_tree(int *arr, int n, int i);
void pre_order(struct node *node, int *arr, int *i);
void in_order(struct node *node, int *arr, int *i);
void post_order(struct node *node, int *arr, int *i);

int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
    struct node *tree = array_to_tree(a, 10, 0);
    int pre[10];
    int pre_expected[10] = {1, 2, 4, 8, 9, 5, 11, 3, 6, 7};
    int j = 0;
    pre_order(tree, pre, &j);
    for (int i = 0; i < 10; i += 1) assert(pre_expected[i] == pre[i]);

    int in[10];
    int in_expected[10] = { 8, 4, 9, 2, 11, 5, 1, 6, 3, 7 };
    j = 0;
    in_order(tree, in, &j);
    for (int i = 0; i < 10; i += 1) assert(in_expected[i] == in[i]);

    int post[10];
    int post_expected[10] = { 8, 9, 4, 11, 5, 2, 6, 7, 3, 1 };
    j = 0;
    post_order(tree, post, &j);
    for (int i = 0; i < 10; i += 1) assert(post_expected[i] == post[i]);

    printf("Success!");
    return 0;
}


struct node *array_to_tree(int *arr, int n, int i) {
    if (i >= n || arr[i] == 0) return NULL;

    struct node *node = malloc(sizeof(struct node));
    node->value = arr[i];
    node->left = array_to_tree(arr, n, i * 2 + 1);
    node->right = array_to_tree(arr, n, i * 2 + 2);

    return node;
}

void pre_order(struct node *node, int *arr, int *i) {
    if (node == NULL) return;

    arr[*i] = node->value;
    *i += 1;
    pre_order(node->left, arr, i);
    pre_order(node->right, arr, i);
}

void in_order(struct node *node, int *arr, int *i) {
    if (node == NULL) return;

    in_order(node->left, arr, i);
    arr[*i] = node->value;
    *i += 1;
    in_order(node->right, arr, i);
}

void post_order(struct node *node, int *arr, int *i) {
    if (node == NULL) return;

    post_order(node->left, arr, i);
    post_order(node->right, arr, i);
    arr[*i] = node->value;
    *i += 1;
}
