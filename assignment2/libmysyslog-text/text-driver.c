/* text-driver.c - Text format driver for MySyslog
 *
 * This driver outputs log messages in plain text format:
 * timestamp log_level process message
 *
 * Example:
 * 1439482969 ERROR example-app this is an error
 *
 * Author: VitalikDen0
 * Course: Operating Systems
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

/* Log level names */
static const char* level_names[] = {
  "DEBUG",
  "INFO",
  "WARN",
  "ERROR",
  "CRITICAL"
};

/* Get process name from /proc/self/comm */
static int 
get_process_name (char *buffer, size_t size)
{
  FILE *fp;
  
  fp = fopen ("/proc/self/comm", "r");
  if (!fp)
    {
      snprintf (buffer, size, "unknown");
      return -1;
    }
  
  if (fgets (buffer, size, fp) == NULL)
    {
      snprintf (buffer, size, "unknown");
      fclose (fp);
      return -1;
    }
  
  /* Remove trailing newline */
  size_t len = strlen (buffer);
  if (len > 0 && buffer[len - 1] == '\n')
    buffer[len - 1] = '\0';
  
  fclose (fp);
  return 0;
}

/* Driver write function - called by libmysyslog via dlsym */
int 
driver_write (const char* msg, int level, const char* path)
{
  FILE *log_file;
  time_t current_time;
  char process_name[256];
  const char *level_name;
  
  /* Validate parameters */
  if (!msg || !path)
    {
      fprintf (stderr, "Text driver error: msg and path cannot be NULL\n");
      return -1;
    }
  
  /* Validate log level */
  if (level < 0 || level > 4)
    {
      fprintf (stderr, "Text driver error: Invalid log level %d\n", level);
      return -1;
    }
  
  /* Get current timestamp */
  current_time = time (NULL);
  if (current_time == (time_t)-1)
    {
      fprintf (stderr, "Text driver error: Failed to get current time\n");
      return -1;
    }
  
  /* Get process name */
  get_process_name (process_name, sizeof (process_name));
  
  /* Get level name */
  level_name = level_names[level];
  
  /* Open log file in append mode */
  log_file = fopen (path, "a");
  if (!log_file)
    {
      fprintf (stderr, "Text driver error: Cannot open log file %s: %s\n",
               path, strerror (errno));
      return -1;
    }
  
  /* Write log entry in text format: timestamp level process message */
  fprintf (log_file, "%ld %s %s %s\n",
           (long)current_time,
           level_name,
           process_name,
           msg);
  
  /* Close file */
  if (fclose (log_file) != 0)
    {
      fprintf (stderr, "Text driver error: Failed to close log file\n");
      return -1;
    }
  
  return 0;
}
