/* mysyslog.c - MySyslog library implementation
 *
 * Implements extensible logging with dynamically loaded drivers
 * using dlopen/dlsym/dlclose for plugin architecture.
 *
 * Author: VitalikDen0
 * Course: Operating Systems
 */

#include "mysyslog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dlfcn.h>
#include <unistd.h>
#include <errno.h>

/* Driver library paths */
#define DRIVER_TEXT_PATH "./libmysyslog-text.so"
#define DRIVER_JSON_PATH "./libmysyslog-json.so"

/* System-wide driver paths (for installed packages) */
#define SYSTEM_DRIVER_TEXT_PATH "/usr/lib/mysyslog/libmysyslog-text.so"
#define SYSTEM_DRIVER_JSON_PATH "/usr/lib/mysyslog/libmysyslog-json.so"

/* Get log level name as string */
const char* 
get_level_name (int level)
{
  switch (level)
    {
    case LOG_LEVEL_DEBUG:
      return "DEBUG";
    case LOG_LEVEL_INFO:
      return "INFO";
    case LOG_LEVEL_WARN:
      return "WARN";
    case LOG_LEVEL_ERROR:
      return "ERROR";
    case LOG_LEVEL_CRITICAL:
      return "CRITICAL";
    default:
      return "UNKNOWN";
    }
}

/* Load a driver dynamically using dlopen */
void* 
load_driver (int driver)
{
  const char *driver_path;
  void *handle;
  
  /* Determine driver path based on driver type */
  if (driver == DRIVER_TEXT)
    {
      /* Try local path first, then system path */
      if (access (DRIVER_TEXT_PATH, F_OK) == 0)
        driver_path = DRIVER_TEXT_PATH;
      else
        driver_path = SYSTEM_DRIVER_TEXT_PATH;
    }
  else if (driver == DRIVER_JSON)
    {
      /* Try local path first, then system path */
      if (access (DRIVER_JSON_PATH, F_OK) == 0)
        driver_path = DRIVER_JSON_PATH;
      else
        driver_path = SYSTEM_DRIVER_JSON_PATH;
    }
  else
    {
      fprintf (stderr, "Error: Unknown driver type: %d\n", driver);
      return NULL;
    }
  
  /* Load the shared library */
  handle = dlopen (driver_path, RTLD_LAZY);
  if (!handle)
    {
      fprintf (stderr, "Error loading driver %s: %s\n", 
               driver_path, dlerror ());
      return NULL;
    }
  
  return handle;
}

/* Unload a driver using dlclose */
void 
unload_driver (void* handle)
{
  if (handle)
    {
      dlclose (handle);
    }
}

/* Main logging function */
int 
mysyslog (const char* msg, int level, int driver, int format, 
          const char* path)
{
  void *driver_handle;
  driver_write_func write_func;
  int result;
  
  /* Validate input parameters */
  if (!msg || !path)
    {
      fprintf (stderr, "Error: msg and path cannot be NULL\n");
      return -1;
    }
  
  if (level < LOG_LEVEL_DEBUG || level > LOG_LEVEL_CRITICAL)
    {
      fprintf (stderr, "Error: Invalid log level: %d\n", level);
      return -1;
    }
  
  /* Load the appropriate driver */
  driver_handle = load_driver (driver);
  if (!driver_handle)
    {
      return -1;
    }
  
  /* Clear any existing error */
  dlerror ();
  
  /* Get the write function from the driver */
  write_func = (driver_write_func) dlsym (driver_handle, "driver_write");
  
  /* Check for errors in dlsym */
  char *error = dlerror ();
  if (error != NULL)
    {
      fprintf (stderr, "Error loading driver_write function: %s\n", error);
      unload_driver (driver_handle);
      return -1;
    }
  
  /* Call the driver's write function */
  result = write_func (msg, level, path);
  
  /* Unload the driver */
  unload_driver (driver_handle);
  
  return result;
}
