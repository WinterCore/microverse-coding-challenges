#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct node {
    int key;
    void *value;
    struct node *next;
};

struct hash {
    int size;
    struct node **list;
};

struct hash *hash_create();
void hash_set(struct hash *hash, int key, void *value);
void *hash_get(struct hash *hash, int key);
void *hash_delete(struct hash *hash, int key);
void hash_destroy(struct hash *hash, bool clear_data);

void ls_push(struct node **node, void *value);
void *ls_pop(struct node **node);
void ls_reverse(struct node **head);

void graph(struct hash *hash, struct node **result);
void traverse_first(struct hash *hash, struct hash *visited, struct node **result, int current);


int main() {

    struct hash *hash = hash_create();
    int *a = malloc(sizeof(int) * 1);
    a[0] = 2;
    hash_set(hash, 0, a);

    a = malloc(sizeof(int) * 1);
    a[0] = 4;
    hash_set(hash, 1, a);

    a = malloc(sizeof(int) * 3);
    a[0] = 5;
    a[1] = 0;
    a[2] = 3;
    hash_set(hash, 2, a);

    a = malloc(sizeof(int) * 1);
    a[0] = 2;
    hash_set(hash, 3, a);

    a = malloc(sizeof(int) * 2);
    a[0] = 1;
    a[1] = 5;
    hash_set(hash, 4, a);

    a = malloc(sizeof(int) * 2);
    a[0] = 4;
    a[1] = 2;
    hash_set(hash, 5, a);

    struct node *result = NULL;
    graph(hash, &result);
    ls_reverse(&result);

    assert(*(int *) result->value == 0);
    assert(*(int *) result->next->value == 2);
    assert(*(int *) result->next->next->value == 5);
    assert(*(int *) result->next->next->next->value == 4);

    printf("Success!");
    return 0;
}

void traverse_first(struct hash *hash, struct hash *visited, struct node **result, int current) {
    int value = ((int *) hash_get(hash, current))[0];
    if (hash_get(visited, value) != NULL) {
        return;
    }
    int *item = malloc(sizeof(int));
    *item = current;
    bool *tr = malloc(sizeof(bool));
    *tr = true;
    ls_push(result, item);
    hash_set(visited, current, tr);
    traverse_first(hash, visited, result, value);
}

void graph(struct hash *hash, struct node **result) {
    struct hash *visited = hash_create();
    traverse_first(hash, visited, result, 0);
    hash_destroy(visited, true);
}

void hash_set(struct hash *hash, int key, void *value) {
    int i = key % hash->size;
    struct node **head = &hash->list[i];
    while (*head) {
        if ((*head)->key == key) {
            break;
        }
        head = &(*head)->next;
    }

    if (*head == NULL) {
        struct node *new_node = malloc(sizeof(struct node));
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
    struct node *head = hash->list[i];
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
    struct node **node = &hash->list[i];
    while (*node) {
        if ((*node)->key == key) {
            struct node *old = *node;
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
        struct node *head = hash->list[i];
        while (head != NULL) {
            struct node *old = head;
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
