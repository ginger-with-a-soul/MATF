#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
  do { \
    if (!(expr)) \
      osErrorFatal(userMsg); \
  } while (0)
  
static const char* osUsage = "Usage: ./1 filePath";  

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

void osMakePublicDir(const char* fpath);
void osMakePublicDir2(const char* fpath);

int main(int argc, char** argv) {
  
  osAssert(argc == 2, osUsage);
  
  osMakePublicDir(argv[1]);
  //osMakePublicDir2(argv[1]);
  
  exit(EXIT_SUCCESS); 
}

/* prvi nacin: pomocu umask */
void osMakePublicDir(const char* fpath) {
  
  mode_t oldMask = umask(0);
  
  osAssert(mkdir(fpath, 0777) != -1, "dir creation failed");

  umask(oldMask);
}

/* drugi nacin: pomocu chmod */
void osMakePublicDir2(const char* fpath) {
  
  osAssert(mkdir(fpath, 0777) != -1, "dir creation failed");
  
  osAssert(chmod(fpath, 0777) != -1, "chmod failed");
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
  
  perror(userMsg);
  fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
  
  exit(EXIT_FAILURE);
}

