/* Program ilustruje multipleksiranje upotrebom epoll interfejsa */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <sys/epoll.h>

#define check_error(expr,userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define MAX_SIZE (1024)

/* struktura kojom prenosimo informacije epoll instanci */
typedef struct {
	
	int num;
	int fd;
} epollFd_t;

int main(int argc, char** argv) {
	
	check_error(argc > 1, "...");	
	
	/* kreiramo epoll instancu */
	int nfd = argc-1;
	int epollFd = epoll_create(nfd);
	check_error(epollFd != -1, "...");
	
	/* struktura koju treba da inicijalizujemo */
	struct epoll_event currFd;
	for (int i=0; i < argc-1;i++){
		
		/* otvaramo fajl deskriptor fajla */
		int fd = open(argv[i+1], O_RDONLY|O_NONBLOCK);
		check_error(fd != -1, "...");
		/* alociramo prostor za podatke koje prenosimo kroz epoll */
		epollFd_t* p = malloc(sizeof(epollFd_t));
		check_error(p != NULL, "...");
		
		/* inicijalizujemo podatke */
		p->fd = fd;
		p->num = i;
		
		memset(&currFd, 0, sizeof(struct epoll_event));
		
		/* postavljamo akcije koje nadgledamo */
		currFd.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		/* postavljamo pokazivac na strukturu koja cuva podatke */
		currFd.data.ptr = (void*)p;
		
		/* ubacujemo novi fajl deskriptor u epoll instancu */
		check_error(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &currFd) != -1, "");
	}
	
	/* alociramo prostor za aktivne fajl deskriptore */
	struct epoll_event* readyEvents = malloc(sizeof(struct epoll_event)*10);
	check_error(readyEvents != NULL, "...");
	
	/* dok god imamo aktivne fajl deskriptore */
	while (nfd) {
		
		/* cekamo na dogadjaj */
		int noOfActive = epoll_wait(epollFd, readyEvents, 10, -1);
		check_error(noOfActive != -1, "...");
		
		/* u petlji, iteriramo kroz dogadjaje */
		for (int i = 0; i < noOfActive; i++) {
			
			/* ako je fajl deskriptor spreman za citanje */
			if (readyEvents[i].events & EPOLLIN) {
				
				/* dohvatamo pokazivac na podake iz epoll instance */
				epollFd_t* p = (epollFd_t*)readyEvents[i].data.ptr;
				printf("Spreman: %d\n", p->num);
				/* citamo sadrzaj fajla */
				char buffer[MAX_SIZE];
				int readBytes = read(p->fd, buffer, MAX_SIZE);
				check_error(readBytes != -1, "...");
				
				/* terminisemo sadrzaj  i prikazujemo poruku */
				buffer[readBytes] = 0;
				printf("%d: %s\n", p->num, buffer);
			}
			/* ako se desila greska */
			else if (readyEvents[i].events & (EPOLLERR | EPOLLHUP)){
				
				/* dohvatamo pokazivac na podake iz epoll instance */
				epollFd_t* p = (epollFd_t*)readyEvents[i].data.ptr;
				printf("Zatvaram: %d\n", p->num);
				
				/* zatvaramo fajl deskriptor i oslobadjamo resurse */
				close(p->fd);				
				
				free(p);
				nfd--;
			}
		}
	}
	
	/* na kraju zatvaramo epoll instancu */
	close(epollFd);
	free(readyEvents);
		
	exit(EXIT_SUCCESS);
}
