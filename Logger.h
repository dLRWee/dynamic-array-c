#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

enum LogLevel
{
    INFO, WARNING, ERROR
};

#define LOG(level, ...) logger_print(level, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) logger_print(INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) logger_print(WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) logger_print(ERROR, __FILE__, __LINE__, __VA_ARGS__)

// Converts the LogLevel value to string
const char* log_level_to_string(enum LogLevel level);

// Prints log information to the console
void logger_print(enum LogLevel level, const char* file, int line, const char* format, ...);

#endif