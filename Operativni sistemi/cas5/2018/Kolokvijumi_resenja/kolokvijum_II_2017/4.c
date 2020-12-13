#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
  do { \
    if (!(expr)) \
      osErrorFatal(userMsg); \
  } while (0)

static const char* osUsage = "Usage: ./1 srcPath destPath";  

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

void osMoveFile(const char* srcPath, const char* destPath);
void osMoveFile2(const char* srcPath, const char* destPath);
void osMoveFile3(const char* srcPath, const char* destPath);

int main(int argc, char** argv) {
  
  osAssert(argc == 3, osUsage);
  
  osMoveFile3(argv[1], argv[2]);
  
  exit(EXIT_SUCCESS); 
}

void osMoveFile(const char* srcPath, const char* destPath) {
  
  char *sPath = realpath(srcPath, NULL);
  char *dPath = realpath(destPath, NULL);
  
  osAssert(sPath != NULL, "source file must exist");
  
  /* pre pozivanja strcmp moramo da se uverimo da nijedna putanja
   * nije NULL.
   * u suprotnom, moze doci do segmentation fault-a
   */
  if (sPath != NULL && dPath != NULL) {
    osAssert(strcmp(sPath, dPath) != 0, "File paths must be different");
  }
  
  /* oslobadjanje dinamicki alociranih promenljivih */
  free(sPath);
  free(dPath);
  
  struct stat fInfo;
  osAssert(stat(srcPath, &fInfo) != -1, "stat failed");
  
  int srcFd = open(srcPath, O_RDONLY);
  mode_t oldMask = umask(0);
  int destFd = open(destPath, O_CREAT | O_WRONLY | O_TRUNC, fInfo.st_mode);
  umask(oldMask);
  
  int bufSize = 1<<13u;
  char* buf = malloc(bufSize);
  
  osAssert(buf != NULL, "allocation failed");
  
  int bytesRead = 0;
  
  while ((bytesRead = read(srcFd, buf, bufSize)) > 0) {
   
    osAssert(write(destFd, buf, bytesRead) == bytesRead, "write failed");
  }
  
  osAssert(bytesRead == 0, "read failed");
  
  free(buf);
  close(srcFd);
  close(destFd);
  
  osAssert(unlink(srcPath) != -1, "unlink failed");
}

void osMoveFile2(const char* srcPath, const char* destPath) {
  
  char *sPath = realpath(srcPath, NULL);
  char *dPath = realpath(destPath, NULL);
  
  osAssert(sPath != NULL, "source file must exist");
  
  /* pre pozivanja strcmp moramo da se uverimo da nijedna putanja
   * nije NULL.
   * u suprotnom, moze doci do segmentation fault-a
   */
  if (sPath != NULL && dPath != NULL) {
    osAssert(strcmp(sPath, dPath) != 0, "File paths must be different");
  }
  
  /* oslobadjanje dinamicki alociranih promenljivih */
  free(sPath);
  free(dPath);
  
  /* u slucaju da fajl na destPath postoji */
  if (access(destPath, F_OK) == 0){
    
    /* fajl mora da se obrise pre poziva link funkcije */
    osAssert(unlink(destPath)!= -1, "unlink failed");;
  }
  
  /* linkuje se nova putanja */
  osAssert(link(srcPath, destPath)!= -1, "unlink failed");
  
  /* brise se fajl sa srcPath */
  osAssert(unlink(srcPath) != -1, "unlink failed");
}

void osMoveFile3(const char* srcPath, const char* destPath) {
  
  char *sPath = realpath(srcPath, NULL);
  char *dPath = realpath(destPath, NULL);
  
  osAssert(sPath != NULL, "source file must exist");
  
  /* pre pozivanja strcmp moramo da se uverimo da nijedna putanja
   * nije NULL.
   * u suprotnom, moze doci do segmentation fault-a
   */
  if (sPath != NULL && dPath != NULL) {
    osAssert(strcmp(sPath, dPath) != 0, "File paths must be different");
  }
  
  /* oslobadjanje dinamicki alociranih promenljivih */
  free(sPath);
  free(dPath);
  
  /* kreira se fajl na destPath */
  osAssert(rename(srcPath, destPath) != -1, "rename failed");
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
  
  perror(userMsg);
  fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
  
  exit(EXIT_FAILURE);
}

