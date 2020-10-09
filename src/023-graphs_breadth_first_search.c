#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct node {
    void *value;
    struct node *next;
    struct node *prev;
};

struct deque {
    struct node *head;
    struct node *tail;
};

struct arr {
    int n;
    int arr[];
};

void ls_push(struct node **node, void *value);
void *ls_pop(struct node **node);
void ls_reverse(struct node **head);

struct deque *create_deque();
bool empty(struct deque *deque);
void push(struct deque *deque, void *value);
void unshift(struct deque *deque, void *value);
void *pop(struct deque *deque);
void *shift(struct deque *deque);

struct hash_node {
    int key;
    void *value;
    struct hash_node *next;
};

struct hash {
    int size;
    struct hash_node **list;
};

struct hash *hash_create();
void hash_set(struct hash *hash, int key, void *value);
void *hash_get(struct hash *hash, int key);
void *hash_delete(struct hash *hash, int key);
void hash_destroy(struct hash *hash, bool clear_data);

void graph(struct hash *hash, struct node **result);
void breadth_first(struct hash *hash, struct hash *visited, struct node **result, int current);


int main() {
    struct hash *hash = hash_create();
    struct arr *a = malloc(sizeof(struct arr) + sizeof(int) * 1);
    a->arr[0] = 2;
    a->n = 1;
    hash_set(hash, 0, a);

    a = malloc(sizeof(struct arr) + sizeof(int) * 1);
    a->arr[0] = 4;
    a->n = 1;
    hash_set(hash, 1, a);

    a = malloc(sizeof(struct arr) + sizeof(int) * 3);
    a->arr[0] = 5;
    a->arr[1] = 0;
    a->arr[2] = 3;
    a->n = 3;
    hash_set(hash, 2, a);

    a = malloc(sizeof(struct arr) + sizeof(int) * 1);
    a->arr[0] = 2;
    a->n = 1;
    hash_set(hash, 3, a);

    a = malloc(sizeof(struct arr) + sizeof(int) * 2);
    a->arr[0] = 1;
    a->arr[1] = 5;
    a->n = 2;
    hash_set(hash, 4, a);

    a = malloc(sizeof(struct arr) + sizeof(int) * 2);
    a->arr[0] = 4;
    a->arr[1] = 2;
    a->n = 2;
    hash_set(hash, 5, a);

    struct node *result = NULL;
    graph(hash, &result);
    ls_reverse(&result);

    assert(*(int *) result->value == 0);
    assert(*(int *) result->next->value == 2);
    assert(*(int *) result->next->next->value == 5);
    assert(*(int *) result->next->next->next->value == 3);
    assert(*(int *) result->next->next->next->next->value == 4);
    assert(*(int *) result->next->next->next->next->next->value == 1);


    printf("Success!");
    return 0;
}

void graph(struct hash *hash, struct node **result) {
    struct hash *visited = hash_create();
    breadth_first(hash, visited, result, 0);
    // hash_destroy(visited, true);
}

void breadth_first(struct hash *hash, struct hash *visited, struct node **result, int current) {
    struct deque *deque = create_deque();
    int *c = malloc(sizeof(int));
    *c = current;
    push(deque, c);
    bool t = malloc(sizeof(bool));
    t = true;
    hash_set(visited, *c, &t);

    while (!empty(deque)) {
        c = shift(deque);
        struct arr *arr = hash_get(hash, *c);
        ls_push(result, c);
        for (int i = 0; i < arr->n; i += 1) {
            if (hash_get(visited, arr->arr[i]) == NULL) {
                push(deque, &arr->arr[i]);
                bool t = malloc(sizeof(bool));
                t = true;
                hash_set(visited, arr->arr[i], &t);
            }
        }
    }
}


struct deque *create_deque() {
    struct deque *deque = malloc(sizeof(struct deque));
    deque->head = NULL;
    deque->tail = NULL;

    return deque;
}

bool empty(struct deque *deque) {
    return deque->head == NULL || deque->tail == NULL;
}

void push(struct deque *deque, void *value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (empty(deque)) {
        deque->head = deque->tail = new_node;
    } else {
        deque->tail->next = new_node;
        new_node->prev = deque->tail;
        deque->tail = new_node;
    }
}

void *pop(struct deque *deque) {
    void *value = deque->tail->value;
    struct node *old = deque->tail;
    if (old->prev) old->prev->next = NULL;
    deque->tail = old->prev;
    free(old);
    return value;
}


void unshift(struct deque *deque, void *value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    if (empty(deque)) {
        deque->head = deque->tail = new_node;
    } else {
        new_node->next = deque->head;
        deque->head->prev = new_node;
        deque->head = new_node;
    }
}

void *shift(struct deque *deque) {
    void *value = deque->head->value;
    struct node *old = deque->head;
    if (old->next) old->next->prev = NULL;
    deque->head = old->next;
    free(old);
    return value;
}



void hash_set(struct hash *hash, int key, void *value) {
    int i = key % hash->size;
    struct hash_node **head = &hash->list[i];
    while (*head) {
        if ((*head)->key == key) {
            break;
        }
        head = &(*head)->next;
    }

    if (*head == NULL) {
        struct hash_node *new_node = malloc(sizeof(struct node));
        if (new_node == NULL) {
            fprintf(stderr, "Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        new_node->key   = key;
        new_node->value = value;
        new_node->next  = NULL;
        *head = new_node;
    } else {
        (*head)->value = value;
    }
}

struct hash *hash_create() {
    struct hash *hash = malloc(sizeof(struct hash));
    hash->size = 10;
    hash->list = malloc(sizeof(struct hash *) * hash->size);
    for (int i = 0; i < hash->size; i += 1)
        hash->list[i] = NULL;
    return hash;
}

void *hash_get(struct hash *hash, int key) {
    int i = key % hash->size;
    struct hash_node *head = hash->list[i];
    while (head) {
        if (head->key == key) {
            return head->value;
        }
        head = head->next;
    }
    return NULL;
}

void *hash_delete(struct hash *hash, int key) {
    int i = key % hash->size;
    struct hash_node **node = &hash->list[i];
    while (*node) {
        if ((*node)->key == key) {
            struct hash_node *old = *node;
            void *value      = old->value;
            *node = old->next;
            free(old);
            return value;
        }
    }
    return NULL;
}

void hash_destroy(struct hash *hash, bool clear_data) {
    for (int i = 0; i < hash->size; i += 1) {
        struct hash_node *head = hash->list[i];
        while (head != NULL) {
            struct hash_node *old = head;
            head = head->next;
            if (clear_data)
                free(old->value);
            free(old);
        }
    }

    free(hash->list);
    free(hash);
}

void ls_push(struct node **node, void *value) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next  = *node;

    *node = new_node;
}

void *ls_pop(struct node **node) {
    void *value = (*node)->value;
    struct node *old = *node;
    *node = (*node)->next;
    free(old);
    return value;
}

void ls_reverse(struct node **head) {
    struct node *prev = NULL, *current = *head, *next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }

    *head = prev;
}
