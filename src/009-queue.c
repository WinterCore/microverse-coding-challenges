#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct node {
    int value;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
};

void add(struct queue *queue, int value);
int delete(struct queue *queue);

int main() {
    struct queue *queue = malloc(sizeof(struct queue));
    add(queue, 3);
    add(queue, 5);
    assert(delete(queue) == 3);
    add(queue, 2);
    add(queue, 7);
    assert(delete(queue) == 5);

    assert(delete(queue) == 2);
    assert(delete(queue) == 7);

    printf("Success!");

    return 0;
}


void add(struct queue *queue, int value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next  = queue->head;


    if (!queue->head) {
        queue->tail = queue->head = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
}

bool empty(struct queue *queue) {
    return !queue->head || !queue->tail;
}


int delete(struct queue *queue) {
    int value = queue->head->value;
    struct node *old = queue->head;
    queue->head = old->next;
    free(old);
    return value;
}
