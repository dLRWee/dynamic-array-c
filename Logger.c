#include <stdarg.h>
#include <stdio.h>

#include "Logger.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const char* log_level_to_string(enum LogLevel level)
{
    switch (level)
    {
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}

void logger_print(enum LogLevel level, const char* file, int line, const char* format, ...)
{
    const char* color;
    switch (level)
    {
        case INFO:    color = ANSI_COLOR_GREEN;  break;
        case WARNING: color = ANSI_COLOR_YELLOW; break;
        case ERROR:   color = ANSI_COLOR_RED;    break;
        default:      color = ANSI_COLOR_RESET;  break;
    }

    char header[256];
    switch (level)
    {
        case INFO:
            sprintf_s(header, sizeof(header), "[%s%s%s]", color, log_level_to_string(level), ANSI_COLOR_RESET);
            break;

        default:
            sprintf_s(header, sizeof(header), "[%s%s%s] in %s at line %d:", color, log_level_to_string(level), ANSI_COLOR_RESET, file, line);
            break;
    }

    va_list args;
    va_start(args, format);

    printf("%s ", header);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}