#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int binary_tree_height(int tree[], int n, int i);
int max(int a, int b);

int main() {
    int arr1[] = {10, 1, 2, 3, 4, 5, 6};
    int arr2[] = {5, 3, 2, 9, 0, 0, 7, 0, 0, 0, 0, 0, 0, 5, 0};
    int arr3[] = {1, 2, 3, 4, 0, 5, 6, 7, 8, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0};

    assert(binary_tree_height(arr1, sizeof(arr2) / sizeof(arr1[0]), 0) == 4);
    assert(binary_tree_height(arr2, sizeof(arr2) / sizeof(arr2[0]), 0) == 4);
    assert(binary_tree_height(arr3, sizeof(arr3) / sizeof(arr3[0]), 0) == 5);

    printf("Success!");
    return 0;
}

int binary_tree_height(int tree[], int n, int i) {
    if (i >= n || tree[i] == 0) return 0;

    return 1 + max(binary_tree_height(tree, n, i * 2 + 1), binary_tree_height(tree, n, i * 2 + 2));
}

int max(int a, int b) {
    return a > b ? a : b;
}
