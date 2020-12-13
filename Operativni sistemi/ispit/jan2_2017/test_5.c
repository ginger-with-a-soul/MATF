#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <pthread.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)
    
static const char *osUsage = "./5 filePath wordToCheck";

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum);

#define MAX_SIZE (256)

int main(int argc, char** argv) {
	
	int fd = open(argv[1], O_RDWR);
	osAssert(fd != -1, "open failed");
	// nebitan fajl, nepotrebna provera gresaka
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 7;
	lock.l_len = 3;
	// w katanac na 7. bajtu
	fcntl(fd, F_SETLK, &lock);
	
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 39;
	lock.l_len = 3;
	// r katanac na 39. bajtu
	fcntl(fd, F_SETLK, &lock);
	
	// blokiranje dok korisnik ne unese nesto
	getchar();
	
	close(fd);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum) {
    perror(userMsg);
    fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName, functionName, lineNum);
    exit(EXIT_FAILURE);
}
