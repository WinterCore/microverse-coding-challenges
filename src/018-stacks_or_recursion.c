#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    void *value;
    struct node *next, *prev;
};

struct bt_node {
    int value;
    struct bt_node *left, *right;
};

struct deque {
    struct node *head, *tail;
    size_t length;
};

struct deque *create_deque();
void push(struct deque *deque, void *value);
void unshift(struct deque *deque, void *value);
void *pop(struct deque *deque);
void *shift(struct deque *deque);

struct bt_node *array_to_tree(int arr[], int n, int i);
size_t iterative_tree_height(struct bt_node *root);

int main() {
    int a[] = {8, 4, 10, 3, 6, 9, 11}, // 3
        b[] = {2, 7, 5, 2, 6, 0, 9}, // 3
        c[] = {1, 7, 5, 2, 6, 0, 9, 3, 7, 5, 11, 0, 0, 4, 0}, // 4
        d[] = {5, 3, 2, 9, 0, 0, 7, 0, 0, 0, 0, 0, 0, 5, 0}; // 4

    assert(iterative_tree_height(array_to_tree(a, sizeof(a) / sizeof(a[0]), 0)) == 3);
    assert(iterative_tree_height(array_to_tree(b, sizeof(b) / sizeof(b[0]), 0)) == 3);
    assert(iterative_tree_height(array_to_tree(c, sizeof(c) / sizeof(c[0]), 0)) == 4);
    assert(iterative_tree_height(array_to_tree(d, sizeof(d) / sizeof(d[0]), 0)) == 4);

    printf("Success!");
    return 0;
}

struct deque *create_deque() {
    struct deque *deque = malloc(sizeof(struct deque));
    if (deque == NULL) {
        fprintf(stderr, "Failed to allocate memory.perror");
        exit(EXIT_FAILURE);
    }
    deque->head = NULL;
    deque->tail = NULL;
    deque->length = 0;

    return deque;
}

void push(struct deque *deque, void *value) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    deque->length += 1;

    if (deque->head == NULL || deque->tail == NULL) {
        deque->head = deque->tail = new_node;
    } else {
        deque->tail->next = new_node;
        new_node->prev = deque->tail;
        deque->tail = new_node;
    }
}

void unshift(struct deque *deque, void *value) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    deque->length += 1;
    if (deque->head == NULL || deque->tail == NULL) {
        deque->head = deque->tail = new_node;
    } else {
        deque->head->prev = new_node;
        new_node->next = deque->head;
        deque->head = new_node;
    }
}

void *shift(struct deque *deque) {
    if (deque->length == 0) {
        fprintf(stderr, "The deque is empty!");
        exit(EXIT_FAILURE);
    }
    void *value = deque->head->value;
    struct node *old = deque->head;
    deque->head = old->next;
    if (deque->head)
        deque->head->prev = NULL;
    free(old);
    deque->length -= 1;
    return value;
}

void *pop(struct deque *deque) {
    if (deque->length == 0) {
        fprintf(stderr, "The deque is empty!");
        exit(EXIT_FAILURE);
    }
    void *value = deque->tail->value;
    struct node *old = deque->tail;
    deque->tail = old->prev;
    if (deque->tail)
        deque->tail->next = NULL;
    free(old);
    deque->length -= 1;
    return value;
}

struct bt_node *array_to_tree(int arr[], int n, int i) {
    if (i >= n || arr[i] == 0) return NULL;

    struct bt_node *node = malloc(sizeof(struct bt_node));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }
    node->value = arr[i];
    node->left  = array_to_tree(arr, n, i * 2 + 1);
    node->right = array_to_tree(arr, n, i * 2 + 2);

    return node;
}

size_t iterative_tree_height(struct bt_node *root) {
    struct deque *deque = create_deque();

    size_t height = 0, width = 0;

    push(deque, root);

    while (1) {
        width = deque->length;
        if (width == 0) return height;

        height += 1;
        while (width--) {
            struct bt_node *node = shift(deque);
            if (node->left) push(deque, node->left);
            if (node->right) push(deque, node->right);
        }
    }

    return height;
}
