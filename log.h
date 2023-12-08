// log.h
#ifndef LOG_H
#define LOG_H

#include <time.h>

typedef struct {
    char message[256];
    time_t timestamp;
} LogEvent;

typedef struct {
    LogEvent events[1000];
    int count;
} Log;

Log* create_log();
void log_event(Log* log, const char* message, int patient_id, int timestamp);
void save_log_to_file(const Log* log, const char* filename);
void destroy_log(Log* log);

#endif
