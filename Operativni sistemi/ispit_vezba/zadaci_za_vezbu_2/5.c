#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <errno.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)

#define MAX_SIZE (1024)		

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "./4 filePath word1 word2");
	
	FILE* f = fopen(argv[1], "r+");
	osAssert(f != NULL, "fopen failed");
	
	int fd = fileno(f);
	osAssert(fd != -1, "fileno failed");
	
	struct flock lock;
	char buf[MAX_SIZE];
	int len = strlen("Milivoje");
	
	while (!feof(f)) {
		
		char* error;
		// citamo rec po rec
		fscanf(f, "%s", buf);
		
		// ako nije Milivoje, prelazimo na sledecu rec
		if (strcmp(buf, "Milivoje")) {
			continue;
		}
		
		// pokusavamo da zakljucamo fajl u modu za pisanje
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = ftell(f);
		lock.l_len = -len;
		
		// proveravamo da li je moguce zakljucati
		int result = fcntl(fd, F_GETLK, &lock);
		
		// provera gresaka
		if (result == -1) {
			if (errno != EACCES && errno != EAGAIN) {
				osAssert(0, "lock failed");
			}
		}
		else {
			
			// ako postoje katanci, stampamo informacije o njima
			if (lock.l_type == F_RDLCK) {
				printf("r %ld %jd\n", ftell(f) - len, (intmax_t)lock.l_pid);
			}
			else if (lock.l_type == F_WRLCK) {
				printf("w %ld %jd\n", ftell(f) - len, (intmax_t)lock.l_pid);
			}
			else {
				// ako ne postoje katanci
								
				// zakljucavamo fajl
				osAssert(fcntl(fd, F_SETLK, &lock) != -1, "fcntl failed");
				
				// pomeramo offset i menjamo Milivoja sa Dragutinom
				osAssert(fseek(f, -len, SEEK_CUR) != -1, "fseek failed");
				fprintf(f, "%s", "Dragutin");
				
				/* otljucavanje fajla */
				lock.l_type = F_UNLCK;
				lock.l_whence = SEEK_SET;
				lock.l_start = 0;
				/* nula kao duzina je specijalni znak za zakljucavanje/otkljucavanje 
				 * fajla od pozicija start pa sve do kraja fajla
				 */
				lock.l_len = 0; 
				osAssert(fcntl(fd, F_SETLK, &lock) != -1, "unlocking failed");
			}
		}
	}
	
	fclose(f);
		
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}
