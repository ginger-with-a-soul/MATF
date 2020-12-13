#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <poll.h>
#include <strings.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)

#define MAX_SIZE (256) 
#define BUF_SIZE (1<<13u)

int main(int argc, char** argv) {
	
	osAssert(argc == 2, os_Usage);
	
	unsigned int numFifos = strtol(argv[1], NULL, 10);

	struct pollfd* fileMonitors = calloc(numFifos, sizeof(struct pollfd));
	osAssert(fileMonitors != NULL, "calloc failed");
	int* bytesRead = malloc(numFifos*sizeof(int));
	osAssert(bytesRead != NULL, "malloc failed");
	
	int i;
	char buf[MAX_SIZE];
	for (i = 0; i < numFifos; i++) {
		bytesRead[i] = 0;
		memset(buf, 0, MAX_SIZE);
		sprintf(buf, "/tmp/%d", i);
		fileMonitors[i].fd = open(buf, O_RDONLY | O_NONBLOCK);
		osAssert(fileMonitors[i].fd != -1, "open failed");
		fileMonitors[i].events = POLLIN | POLLHUP | POLLERR;
	}
	
	int read_bytes;
	int numActive = numFifos;
	char localBuf[BUF_SIZE];
	int max_bytes = 0;
	int index = -1;
	while (numActive) {
		
		int events = poll(fileMonitors, numFifos, -1);
		osAssert(events != -1, "poll failed");
		
		
		for (i = 0; i < numFifos; i++) {
			
			if (fileMonitors[i].revents & POLLIN) {
				int totalBytes = 0;
				while((read_bytes = read(fileMonitors[i].fd, localBuf, BUF_SIZE)) > 0) {
					totalBytes += read_bytes;
				}
				
				osAssert(read_bytes != -1, "read failed");
				
				bytesRead[i] += totalBytes;
				
				if (bytesRead[i] > max_bytes) {
					
					max_bytes = bytesRead[i];
					index = i;
				}
				
				fileMonitors[i].revents = 0;
			}
			else if (fileMonitors[i].revents & (POLLHUP | POLLERR)) {
				
				close(fileMonitors[i].fd);
				fileMonitors[i].fd = -1;
				fileMonitors[i].revents = 0;
				fileMonitors[i].events = 0;
				numActive--;
			}
		}		
	}
	
	
	printf("/tmp/%d %d\n", index, max_bytes);	
	
	free(fileMonitors);
	free(bytesRead);
	
	exit(EXIT_SUCCESS);
}
