// structures.h

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <time.h>

typedef struct {
    char message[256];
    time_t timestamp;
} LogEvent;

typedef struct {
    LogEvent events[1000]; // Adjust capacity as needed
    int count;
} Log;

typedef struct {
    char name[50];
    char cpf[12];
    int age;
    int id;
} Patient;

typedef struct {
    int patientId;
    time_t timestamp; // Added time_t field
    char condition[50];
} Examination;

typedef struct {
    int *items;
    int front;
    int rear;
    int capacity;
} Queue;

#endif
