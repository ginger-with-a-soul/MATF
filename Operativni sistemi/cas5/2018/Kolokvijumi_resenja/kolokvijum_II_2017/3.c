#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <time.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
  do { \
    if (!(expr)) \
      osErrorFatal(userMsg); \
  } while (0)
  
#define SECS_PER_DAY (24*60*60)
static const char* osUsage = "Usage: ./1 filePath";  

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

unsigned osNumOfDaysFIleModified(const char* fpath);

int main(int argc, char** argv) {
  
  osAssert(argc == 2, osUsage);
  
  unsigned days = osNumOfDaysFIleModified(argv[1]);
  printf("%u\n", days);
  
  exit(EXIT_SUCCESS); 
}

unsigned osNumOfDaysFIleModified(const char* fpath) {
  
  struct stat fInfo;
  osAssert(stat(fpath, &fInfo) != -1, "stat failed");
  
  time_t now = time(NULL);
  osAssert(now != -1, "time failed");
  
  unsigned days = (now - fInfo.st_mtime)/SECS_PER_DAY;
  return days;
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
  
  perror(userMsg);
  fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
  
  exit(EXIT_FAILURE);
}

