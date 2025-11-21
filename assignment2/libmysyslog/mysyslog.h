/* mysyslog.h - MySyslog extensible logging library header
 *
 * This library provides a flexible logging system with support for
 * multiple output formats through dynamically loaded drivers.
 *
 * Author: VitalikDen0
 * Course: Operating Systems
 */

#ifndef MYSYSLOG_H
#define MYSYSLOG_H

/* Log levels */
#define LOG_LEVEL_DEBUG    0
#define LOG_LEVEL_INFO     1
#define LOG_LEVEL_WARN     2
#define LOG_LEVEL_ERROR    3
#define LOG_LEVEL_CRITICAL 4

/* Driver types */
#define DRIVER_TEXT 0
#define DRIVER_JSON 1

/* Format types */
#define FORMAT_TEXT 0
#define FORMAT_JSON 1

/* Function pointer type for driver write functions */
typedef int (*driver_write_func)(const char* msg, int level, 
                                  const char* path);

/* Main logging function
 *
 * Parameters:
 *   msg    - Message to log
 *   level  - Log level (DEBUG, INFO, WARN, ERROR, CRITICAL)
 *   driver - Driver type (TEXT or JSON)
 *   format - Output format (TEXT or JSON)
 *   path   - Path to log file
 *
 * Returns:
 *   0 on success, -1 on error
 */
int mysyslog(const char* msg, int level, int driver, int format, 
             const char* path);

/* Helper function to get log level name as string */
const char* get_level_name(int level);

/* Helper function to load a driver dynamically */
void* load_driver(int driver);

/* Helper function to unload a driver */
void unload_driver(void* handle);

#endif /* MYSYSLOG_H */
