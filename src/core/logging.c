#include <core/logging.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE* logfile_ptr = NULL;
static LogLevel log_level = LOG_INFO;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

static char log_buffer[LOG_BUFFER_CAPACITY_BYTES];
static size_t log_buffer_index = 0;

void Log_Init(const char* log_file_path, LogLevel min_level)
{
    if (min_level >= LOG_INFO && min_level <= LOG_FATAL) {
        log_level = min_level;
    } else {
        log_level = LOG_INFO;
    }

    pthread_mutex_lock(&log_mutex);
    if (log_file_path != NULL) {
        logfile_ptr = fopen(log_file_path, "a");

        if (logfile_ptr == NULL) {
            fprintf(stderr, "FATAL: Failed to open log file: %s\n", log_file_path);
        } else {
            fprintf(stdout, "INFO: Log file opened: %s\n", log_file_path);
        }
    }
    pthread_mutex_unlock(&log_mutex);

    if (logfile_ptr != NULL) {
        pthread_mutex_lock(&buffer_mutex);

        fputs("----------- NEW VIOXITY SESSION -----------\n", logfile_ptr);
        fflush(logfile_ptr);

        pthread_mutex_unlock(&buffer_mutex);
    }

    log_buffer_index = 0;
    fprintf(stdout, "INFO: Logging initialized...\n");
}

void Log_Destroy(void)
{
    pthread_mutex_lock(&log_mutex);
    pthread_mutex_lock(&buffer_mutex);

    if (logfile_ptr != NULL && log_buffer_index > 0) {
        size_t written = fwrite(log_buffer, 1, log_buffer_index, logfile_ptr);

        if (written != log_buffer_index) {
            fprintf(stderr, "FATAL: Failed to write to log file.\n");
        }

        fputs("----------- END VIOXITY SESSION -----------\n", logfile_ptr);

        fflush(logfile_ptr);
    }

    if (logfile_ptr != NULL) {
        fclose(logfile_ptr);
        logfile_ptr = NULL;
        fputs("INFO: Log file closed.\n", stderr);
    }

    log_buffer_index = 0;

    pthread_mutex_unlock(&buffer_mutex);
    pthread_mutex_unlock(&log_mutex);
    fprintf(stdout, "INFO: Logging destroyed...\n");
}

void Log_Message(
    LogLevel level,
    const char* file,
    int line,
    const char* message,
    ...)
{

    if (level < log_level) {
        return;
    }

    pthread_mutex_lock(&log_mutex);

    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d..%H:%M:%S", timeinfo);

    const char* level_strs[] = { "INFO", "WARN", "ERROR", "FATAL" };
    const char* level_str = (level >= LOG_INFO && level <= LOG_FATAL) ? level_strs[level] : "UNKNOWN";

    char user_message[MAX_LOG_MESSAGE_SIZE];
    va_list args;
    va_start(args, message);
    vsnprintf(user_message, sizeof(user_message), message, args);
    va_end(args);

    char final_message[MAX_LOG_MESSAGE_SIZE + 512];
    int total_len = snprintf(
        final_message,
        sizeof(final_message),
        "[%s] [%s] [%s:%d] %s",
        timestamp,
        level_str,
        file,
        line,
        user_message);

    fputs(final_message, stdout);

    pthread_mutex_unlock(&log_mutex);

    if (total_len > 0 && logfile_ptr != NULL) {
        pthread_mutex_lock(&buffer_mutex);

        if (log_buffer_index + total_len < LOG_BUFFER_CAPACITY_BYTES) {
            memcpy(log_buffer + log_buffer_index, final_message, total_len);
            log_buffer_index += total_len;
        } else {
            fprintf(stderr, "FATAL: Log buffer overflow.\n");
        }

        pthread_mutex_unlock(&buffer_mutex);
    }
}
