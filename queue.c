#include "queue.h"
#include "simulation.h"
#include <stdlib.h>

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(Queue* queue, ExamRecord data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (is_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    queue->size++;
}

ExamRecord dequeue(Queue* queue) {
    if (is_empty(queue)) {
        exit(EXIT_FAILURE);
    }

    Node* temp = queue->front;
    ExamRecord data = temp->data;

    queue->front = temp->next;
    free(temp);

    queue->size--;

    return data;
}

int is_empty(Queue* queue) {
    return queue->size == 0;
}

void destroy_queue(Queue* queue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
