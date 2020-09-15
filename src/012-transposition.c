#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct node {
    char value;
    struct node *next;
    struct node *prev;
};

struct deque {
    struct node *head;
    struct node *tail;
};

struct deque *create_deque();
bool empty(struct deque *deque);
void push(struct deque *deque, char value);
void unshift(struct deque *deque, char value);
char pop(struct deque *deque);
char shift(struct deque *deque);

char *transpose(char *s);

int main() {
    assert(
        strcmp(
            transpose("he was searchign on Bign for signign kigns"),
            "he was searching on Bing for singing kings"
        ) == 0
    );

    assert(
        strcmp(
            transpose("rignadingdiggn!"),
            "ringadingdingg!"
        ) == 0
    );

    assert(
        strcmp(
            transpose("gngngnnggnngggnnn"),
            "nnnnnnnnngggggggg"
        ) == 0
    );

    printf("Success!");

    return 0;
}

char *transpose(char *s) {
    struct deque *deque = create_deque();
    char *out = malloc(strlen(s) + 1);
    int i = 0;
    while (*s) {
        if (*s == 'n') {
            unshift(deque, 'n');
        } else if (*s == 'g') {
            push(deque, 'g');
        } else {
            while (!empty(deque)) out[i++] = shift(deque);
            out[i++] = *s;
        }
        s += 1;
    }
    while (!empty(deque)) out[i++] = shift(deque);
    out[i] = '\0';

    return out;
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

void push(struct deque *deque, char value) {
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

char pop(struct deque *deque) {
    char value = deque->tail->value;
    struct node *old = deque->tail;
    if (old->prev) old->prev->next = NULL;
    deque->tail = old->prev;
    free(old);
    return value;
}


void unshift(struct deque *deque, char value) {
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

char shift(struct deque *deque) {
    char value = deque->head->value;
    struct node *old = deque->head;
    if (old->next) old->next->prev = NULL;
    deque->head = old->next;
    free(old);
    return value;
}

