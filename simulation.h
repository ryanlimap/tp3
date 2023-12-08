// simulation.h

#include "structures.h"
#ifndef SIMULATION_H
#define SIMULATION_H


Log* create_log();
void log_event(Log *log, const char *message);
void save_log_to_file(const Log *log, const char *filename);

Queue* create_queue(int capacity);
int is_empty(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);

void simulate_process();

#endif
