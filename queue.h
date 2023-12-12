#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int patient_id;
    int timestamp;
    int condition;
} ExamRecord;

typedef struct Node {
    ExamRecord data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue* create_queue();
void enqueue(Queue *queue, ExamRecord data);
ExamRecord dequeue(Queue *queue);
int is_empty(Queue* queue);
void destroy_queue(Queue* queue);

#endif
