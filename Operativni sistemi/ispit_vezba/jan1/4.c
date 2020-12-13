#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)

#define osCheckPthread(pthreadErr, userMsg) \
    do { \
      int __pthreadErr = (pthreadErr); \
      if (__pthreadErr > 0) { \
        errno = __pthreadErr; \
        osAssert(false, userMsg); \
      } \
    } while (0)
    
static const char *os_Usage = "./4 pathToFile a b";
    
void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum);                      

int main(int argc, char** argv) {
	
	osAssert(argc == 4, os_Usage);
	
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);
	
	int fd = open(argv[1], O_RDWR);
	osAssert(fd != -1, "open failed");
	
	struct flock fLock;
	fLock.l_type = F_WRLCK;
	fLock.l_whence = SEEK_SET;
	fLock.l_start = a;
	fLock.l_len = b;
	
	osAssert(fcntl(fd, F_GETLK, &fLock) != -1, "flock failed");
	switch (fLock.l_type) {
		case F_UNLCK:
			printf("Unlocked\n");
			break;
		case F_RDLCK:
			printf("Shared lock\n");
			break;	
		case F_WRLCK:
			printf("Exclusive lock\n");
			break;
		default:
			break;
	} 
	
	close(fd);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum) {
    perror(userMsg);
    fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName, functionName, lineNum);
    exit(EXIT_FAILURE);
}
