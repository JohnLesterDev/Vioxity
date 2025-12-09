#ifndef LOGGING_H
#define LOGGING_H

#define MAX_LOG_MESSAGE_SIZE 2048
#define LOG_BUFFER_CAPACITY_BYTES (15 * 1024 * 1024)

typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

void Log_Init(const char* log_file_path, LogLevel min_level);
void Log_Destroy(void);

void Log_Message(
    LogLevel level,
    const char* file,
    int line,
    const char* message,
    ...);

#define LOG_INFO(...) Log_Message(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) Log_Message(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Log_Message(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) Log_Message(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif