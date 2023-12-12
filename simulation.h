#ifndef SIMULATION_H
#define SIMULATION_H

#include "queue.h"
#include "log.h"

typedef struct {
    Queue* patient_queue;
    Queue* exam_queue;
    Log* log;
} Simulation;

int generate_random_time(int min, int max);
int generate_random_condition();
Simulation* create_simulation();
void simulate_time_step(Simulation* sim, int time_step);
void update_and_print_metrics(Simulation* sim);
void destroy_simulation(Simulation* sim);
int is_empty_exam_queue(Queue* queue);
void enqueue_exam(Queue* queue, ExamRecord exam);
ExamRecord dequeue_exam(Queue* queue);

#endif
