#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/epoll.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)

#define MSG_LEN (256)
#define MAX_EVENTS (8)
#define EPOLL_TIMEOUT_BLCK (-1)

int main(int argc, char **argv) {
    osAssert(argc == 2, os_Usage);
    
    /**
     * Create epoll instance
     * */
    unsigned numOfFIFOs = atoi(argv[1]);
    int epollFd = epoll_create(numOfFIFOs);
    osAssert(-1 != epollFd, "Creating epoll instance failed");
    char buffer[1024];
    /**
     * Add all FIFOs to ready list
     * */
    struct epoll_event currentEvent;
    for (unsigned i = 0; i < numOfFIFOs; ++i) {
        /**
         * Prepare events struct
         * */
        memset(&currentEvent, 0, sizeof currentEvent);
        currentEvent.events |= EPOLLIN;
        
        /**
         * Get file descriptor and register it
         * */
        memset(buffer, 0, 1024);
        sprintf(buffer, "/tmp/%u", i);
        currentEvent.data.fd = open(buffer, O_RDONLY | O_NONBLOCK);
        osAssert(-1 != currentEvent.data.fd, "Opening FIFO failed");
        osAssert(-1 != epoll_ctl(epollFd, EPOLL_CTL_ADD, currentEvent.data.fd, &currentEvent), "Registering epoll event failed");
    }
    
    /**
     * Query for events until all FIFOs are closed
     * */
    struct epoll_event readyList[MAX_EVENTS];
    while (numOfFIFOs) {
        /**
         * Get events
         * */
        int numOfReadyEvents;
        osAssert(-1 != (numOfReadyEvents = 
                        epoll_wait(epollFd, readyList, MAX_EVENTS, EPOLL_TIMEOUT_BLCK)), 
                                   "Waiting for ready events failed");
        
        /**
         * Process events
         * NOTE: Assuming that message wil be MSG_LEN at most
         * */
        char buf[MSG_LEN];
        for (int i = 0; i < numOfReadyEvents; ++i) {
            /**
             * FIFO write end closed, fd automatically gets removed from interest list
             * */
            if (readyList[i].events & EPOLLIN) {
                /**
                 * Reading from FIFO
                 * */
                 int bytesRead;
                 osAssert(-1 != (bytesRead = read(readyList[i].data.fd, buf, MSG_LEN)), 
                         "Reading from FIFO failed");
                 buf[bytesRead - 1] = 0; /* terminiranje ucitanog stringa */
                 
                 if (bytesRead == 0) {
					close(readyList[i].data.fd);
					--numOfFIFOs;
					continue;
				 }
				 else {
					int i = 0, j = bytesRead - 2; /* -2 zbog ubijanja novog reda */
					while (i<=j) {
						
						if (buf[i] != buf[j]) {
							break;
						}
						i++;
						j--;
					} 
					
					if (j<=i) {
						printf("%s %d\n", buf, 1);
					}
					else {
						printf("%s %d\n", buf,0);
					}
				 }
            } else if (readyList[i].events & (EPOLLHUP | EPOLLERR)) {
                /**
                 * Closing FIFO
                 * */
                printf("FIFO closed - closing underlying file descriptor.\n");
                close(readyList[i].data.fd);
                --numOfFIFOs;
            }
        }
    }
    
    close(epollFd);
    return 0;
}
