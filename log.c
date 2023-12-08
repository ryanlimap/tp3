// log.c
#include "log.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>

Log* create_log() {
    Log* log = (Log*)malloc(sizeof(Log));
    if (log == NULL) {
        exit(EXIT_FAILURE);
    }
    log->count = 0;
    return log;
}

void log_event(Log* log, const char* message, int patient_id, int timestamp) {
    if (log->count < 1000) {
        LogEvent* event = &(log->events[log->count]);
        snprintf(event->message, sizeof(event->message), "%s - Patient ID: %d, Timestamp: %d", message, patient_id, timestamp);
        event->timestamp = time(NULL);
        log->count++;
    }
}

void save_log_to_file(const Log* log, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < log->count; i++) {
        fprintf(file, "%s\n", log->events[i].message);
    }

    fclose(file);
}

void destroy_log(Log* log) {
    free(log);
}
