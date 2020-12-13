#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <limits.h>
#include <string.h>
#include <ftw.h>
#include <time.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
  do { \
    if (!(expr)) \
      osErrorFatal(userMsg); \
  } while (0)
  
#define SECS_PER_DAY (24*60*60)
#define UNUSED(x)    ((void)x)

static const char* osUsage = "Usage: ./1 dirPath destPath";  
static char* dirPath = NULL;

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

unsigned osNumOfDaysFIleModified(const char* fpath);
void osMoveFile(const char* srcPath, const char* destPath);
void osMakePublicDir(const char* fpath);
bool osIsPublicFile(const char* fpath);
int processFile(const char* fpath, const struct stat *sb, int typeflag, struct FTW* ftwbuf);

int main(int argc, char** argv) {
  
  osAssert(argc == 3, osUsage);

  dirPath = argv[2];
  osMakePublicDir(argv[2]);
  
  osAssert(nftw(argv[1], processFile, 50, 0) != -1, "nftw failed");
  
  exit(EXIT_SUCCESS); 
}


int processFile(const char* fpath, const struct stat *sb, int typeflag, struct FTW* ftwbuf) {
  
  UNUSED(sb);
  
  if (typeflag == FTW_F) {

    if (osIsPublicFile(fpath)) {

      unsigned days = osNumOfDaysFIleModified(fpath);
      
      if (days < 30) {
	
	char* newPath = malloc(strlen(dirPath) + 2 + strlen(fpath + ftwbuf->base));
	strcpy(newPath, dirPath);
	strcat(newPath,"/");
	strcat(newPath, fpath + ftwbuf->base);
	
	osMoveFile(fpath, newPath);
	
	free(newPath);
      }
      else {
	
	osAssert(unlink(fpath) != -1, "unlink failed");
      }
    }
  }
  
  return 0;
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

unsigned osNumOfDaysFIleModified(const char* fpath) {
  
  struct stat fInfo;
  osAssert(stat(fpath, &fInfo) != -1, "stat failed");
  
  time_t now = time(NULL);
  osAssert(now != -1, "time failed");
  
  unsigned days = (now - fInfo.st_mtime)/SECS_PER_DAY;
  return days;
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

void osMakePublicDir(const char* fpath) {
  
  mode_t oldMask = umask(0);
  
  osAssert(mkdir(fpath, 0777) != -1, "dir creation failed");

  umask(oldMask);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
  
  perror(userMsg);
  fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
  
  exit(EXIT_FAILURE);
}

