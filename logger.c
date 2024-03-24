#include <stdarg.h>
#include <time.h>
#include "logger.h"


static const char* levels[] = {
    "[\x1B[1;91mFATAL\x1B[0m]:",
    "[\x1B[1;31mERR\x1B[0m]:",
    "[\x1B[1;92mOK\x1B[0m]:",
    "[\x1B[1;93mWARN\x1B[0m]:",
    "[\x1B[1;37mINFO\x1B[0m]:",
    "[\x1B[1;96mDEBUG\x1B[0m]:"
};

static const char* levels_file[] = {
    "[FATAL]:",
    "[ERR]:",
    "[OK]:",
    "[WARN]:",
    "[INFO]:",
    "[DEBUG]:"
};

#ifdef _WIN32
#include <Windows.h>

static HANDLE s_hConsole;
static DWORD  s_dwOrigMode;

void logger_init(void)
{
    DWORD dwMode;

    s_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(s_hConsole, &dwMode);

    s_dwOrigMode = dwMode;
    dwMode      |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(s_hConsole, dwMode);
}

void logger_clear(void)
{
    SetConsoleMode(s_hConsole, s_dwOrigMode);
}
#endif

void logger_log(log_level_t level, const char* fmt, ...)
{
    time_t  now;
    va_list args;
    char    timestamp[32];

    now = time(NULL);
    strftime(timestamp, 32, "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    va_start(args, fmt);
    printf("%s %-19s ", timestamp, levels[level]);
    vprintf(fmt, args);
    va_end(args);
}

void logger_log_f(log_level_t level, FILE* fp, const char* fmt, ...)
{
    time_t  now;
    va_list args;
    char    timestamp[32];

    now = time(NULL);
    strftime(timestamp, 32, "%Y-%m-%d %H:%M:%S", localtime(&now));

    va_start(args, fmt);
    fprintf(fp, "%s %-8s ", timestamp, levels_file[level]);
    vfprintf(fp, fmt, args);
    va_end(args);

    fflush(fp);
}

