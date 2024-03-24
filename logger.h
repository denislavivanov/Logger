#ifndef LOGGER_H
#define LOGGER_H

#define LOG_INIT_ERROR   1
#define LOG_INIT_SUCCESS 0

#include <stdio.h>

typedef enum
{
    FATAL,
    ERR,
    OK,
    WARN,
    INFO,
    DEBUG
} log_level_t;

#ifdef _WIN32
    void logger_init(void);
    void logger_clear(void);
#endif

/* Console logging */
void logger_log(log_level_t level, const char* fmt, ...);

/* File logging */
void logger_log_f(log_level_t level, FILE* fp, const char* fmt, ...);

#endif
