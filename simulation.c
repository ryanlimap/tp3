// simulation.c

#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Log* create_log() {
    Log *log = (Log*)malloc(sizeof(Log));
    log->count = 0;
    return log;
}

void log_event(Log *log, const char *message) {
    if (log->count < 1000) { // Check capacity
        LogEvent newEvent;
        snprintf(newEvent.message, sizeof(newEvent.message), "[%s] %s", __TIME__, message);
        newEvent.timestamp = time(NULL);
        log->events[log->count++] = newEvent;
    }
}

void save_log_to_file(const Log *log, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < log->count; ++i) {
            fprintf(file, "[%ld] %s\n", log->events[i].timestamp, log->events[i].message);
        }
        fclose(file);
    }
}

Queue* create_queue(int capacity) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(sizeof(int) * capacity);
    queue->front = queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

int is_empty(Queue *queue) {
    return queue->front == -1;
}

void enqueue(Queue *queue, int item) {
    if (is_empty(queue)) {
        queue->front = queue->rear = 0;
        queue->items[queue->rear] = item;
    } else {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->items[queue->rear] = item;
    }
}

int dequeue(Queue *queue) {
    int item = -1;
    if (!is_empty(queue)) {
        item = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->capacity;
        }
    }
    return item;
}

void simulate_process() {
    Log *log = create_log();
    log_event(log, "Simulation started.");

    // Create queues for examination and report
    Queue *examQueue = create_queue(100);
    Queue *reportQueue = create_queue(100);

    // Simulation loop
    for (int time = 0; time < 43200; time += 10) {
        // Simulate patient arrival
        if ((rand() % 100) < 20) {
            Patient newPatient;
            snprintf(newPatient.name, sizeof(newPatient.name), "Patient%d", time);
            snprintf(newPatient.cpf, sizeof(newPatient.cpf), "CPF%d", time);
            newPatient.age = rand() % 100;
            newPatient.id = time;

            enqueue(examQueue, newPatient.id);
            log_event(log, "Patient arrived for examination.");
        }

        // Simulate X-ray examination
        if (!is_empty(examQueue)) {
            int patientId = dequeue(examQueue);
            Examination newExam;
            newExam.patientId = patientId;
            newExam.timestamp = time;

            // Simulate condition based on probabilities
            float randValue = (float)rand() / RAND_MAX;
            if (randValue < 0.3) {
                snprintf(newExam.condition, sizeof(newExam.condition), "Normal");
            } else if (randValue < 0.5) {
                snprintf(newExam.condition, sizeof(newExam.condition), "Bronchitis");
            } else if (randValue < 0.7) {
                snprintf(newExam.condition, sizeof(newExam.condition), "Pneumonia");
            } else if (randValue < 0.85) {
                snprintf(newExam.condition, sizeof(newExam.condition), "Femur Fracture");
            } else {
                snprintf(newExam.condition, sizeof(newExam.condition), "Appendicitis");
            }

            enqueue(reportQueue, patientId);
            log_event(log, "X-ray examination completed.");
        }

        // Simulate report generation
        if (!is_empty(reportQueue)) {
            int patientId = dequeue(reportQueue);
            // Simulate report preparation time
            int reportTime = 10 + rand() % 21;
            time += reportTime;
            log_event(log, "Report generated.");
        }

        // Update metrics every 10 units of time
        if (time % 10 == 0) {
            // Calculate and display metrics
            // ...

            // Log metrics
            log_event(log, "Metrics updated.");
        }
    }

    log_event(log, "Simulation ended.");
    save_log_to_file(log, "log.txt");
    free(log);
    free(examQueue->items);
    free(examQueue);
    free(reportQueue->items);
    free(reportQueue);
}
