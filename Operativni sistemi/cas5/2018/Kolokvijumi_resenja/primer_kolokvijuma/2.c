#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* makro maskira neupotrebljene promenljive */
#define UNUSED(x)	((void)x)

/* poruka koja definise pravilno pozivanje programa */
static const char* os_Usage = "Usage: ./1 filePath";

/* funkcija kreira novi fajl na putanji filePath */
void osMakeFile(const char* filePath);

int main(int argc, char** argv) {
  
  /* provera broja argumenata komandne linije */
  if (argc == 2) {
    perror(os_Usage);
    exit(EXIT_FAILURE);
  }
  
  /* lokalna promenljiva za pamcenje zateknute vrednosti umaska */
  mode_t oldMask = 0;
  /* umask se postavlja na nula da bi se omogucilo jednostavno
   * kreiranje fajla sa proizvoljnim pravima pristupa 
   */
  oldMask = umask(0);
  
  /* kreira se fajl na prosledjenoj putanji */
  osMakeFile(argv[1]);
  
  /* vraca se zateknuta umask vrednost */ 
  umask(oldMask);
  
  /* postavlja se exit kod */
  exit(EXIT_SUCCESS);
}

/* funkcija kreira novi fajl na putanji filePath */
void osMakeFile(const char* filePath) {
  
  /* definise se zeljeni mod */
  static mode_t defaultMode = 0733;
  int fd = 0;
  
  /* kreira se novi fajl uz pomoc open sistemskog poziva.
   * U zadatku je postavljen zahtev da se prijavi greska ukoliko fajl vec postoji.
   * Da bi se to postiglo koristi se flag O_EXCL, sto dovodi do uspesnog kreiranja
   * fajla samo u slucaju kada fajl na zadatoj putanji ne postoji.
   * Detaljnije man 2 open.
   */
  if ((fd = open(filePath, O_WRONLY | O_CREAT | O_EXCL, defaultMode)) < 0) {
    perror("File creation failed");
    exit(EXIT_FAILURE);
  }
  
  /* zatvara se fajl deksriptor novokreiranog fajla */
  close(fd);
}
