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

bool osIsPublicFile(const char* fpath);

int main(int argc, char** argv) {
  
  osAssert(argc == 2, osUsage);
  
  bool result = osIsPublicFile(argv[1]);
  fprintf(stdout, "%s\n", (result == true) ? "true" : "false");
  
  exit(EXIT_SUCCESS); 
}

bool osIsPublicFile(const char* fpath) {
  
 struct stat fInfo;
 osAssert(stat(fpath, &fInfo) != -1, "stat failed");
 
 osAssert(S_ISREG(fInfo.st_mode), "File not regular");
 
 if ((fInfo.st_mode & S_IROTH) && (fInfo.st_mode & S_IWOTH))
   return true;
 else
   return false;
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
  
  perror(userMsg);
  fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
  
  exit(EXIT_FAILURE);
}

