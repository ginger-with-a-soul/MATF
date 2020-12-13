#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <pwd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* makro maskira neupotrebljene promenljive */
#define UNUSED(x)	((void)x)
  
/* poruka koja definise pravilno pozivanje programa */
static const char* os_Usage = "Usage: ./1 filePath";

/* funkcija vraca ukupan broj korisnika sistema u vlasnickoj grupi fajla */
int osNumberOfUsersInGroup(const char* filePath);

int main(int argc, char** argv) {
  
  /* provera broja argumenata komandne linije */
  if (argc != 2) {
    perror(os_Usage);
    exit(EXIT_FAILURE);
  }
  
  /* pronalazi se ukupan broj korisnika sistema u vlasnickoj grupi fajla */
  int users = osNumberOfUsersInGroup(argv[1]);
  
  /* stampa se pronadjeni broj korisnika */
  printf("%d\n", users);
  
  /* postavlja se exit kod */
  exit(EXIT_SUCCESS);
}
/* funkcija vraca ukupan broj korisnika sistema u vlasnickoj grupi fajla */
int osNumberOfUsersInGroup(const char* filePath) {
  
 /* dobijanje informacija o fajlu */
 struct stat fInfo;
 if (stat(filePath, &fInfo) == -1) {
   perror("File stat failed");
   exit(EXIT_FAILURE);
 }
 /* inicijalno, broj korisnika u vlasnickoj grupi fajla je nula */
 int users = 0;
 
 /* passwd fajl se premotava na pocetak */
 setpwent();
 struct passwd* entry = NULL;
 /* dok se ne dodje do kraja fajla */
 while((entry = getpwent()) != NULL) {
   
   /* poredi se gid korisnika sa gid-om vlasnicke grupe */
   if (entry->pw_gid == fInfo.st_gid)
     /* ako su isti, uvecava se brojac korisnika */
     users++;
 }
 /* zatvara se passwd fajl */
 endpwent();
 
 /* vraca se ukupan broj korisnika u vlasnickoj grupi fajla */
 return users;
}

    