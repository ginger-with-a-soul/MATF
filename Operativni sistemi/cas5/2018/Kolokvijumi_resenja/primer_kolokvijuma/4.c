#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <string.h>
#include <limits.h>

/* makro maskira neupotrebljene promenljive */
#define UNUSED(x)	((void)x)

/* poruka koja definise pravilno pozivanje programa */
static const char* os_Usage = "Usage: ./1 destPath srcPath position";

/* funkcija nadovezuje fajlove od pozicije pos */
void osCatFileFromPos(const char* destPath, const char* srcPath, const off_t pos);

int main(int argc, char** argv) {
  
  /* provera broja argumenata komandne linije */
  if (argc != 4) {
    perror(os_Usage);
    exit(EXIT_FAILURE);
  }
  
  /* pozicija se pretvara iz stringa u broj */
  long pos = strtol(argv[3], 0, 10);
  /* vrsi se nadovezivanje fajlova */
  osCatFileFromPos(argv[1], argv[2], (off_t)pos);
  
  /* postavlja se exit kod */
  exit(EXIT_SUCCESS);
}

/* funkcija nadovezuje fajlove od pozicije pos */
void osCatFileFromPos(const char* destPath, const char* srcPath, const off_t pos) {
 
  /* kreiraju se pune putanje fajlova */
  char* path1 = realpath(destPath, NULL);
  char* path2 = realpath(srcPath, NULL);
  
  /* ukoliko se radi o istom fajlu, prijavljuje se greska 
   * Neophodno je proveriti da li je povratna vrednost funkcije realpath
   * NULL, ako jeste ne sme da se prosledi u strcmp jer je to momentalni SEGFAULT
   */
  if (path1 != NULL && path2 != NULL && strcmp(path1, path2) == 0) {
    perror("dest and src must be different");
    exit(EXIT_FAILURE);
  }
  /* oslobadja se koriscena memorija */
  if (path1 != NULL)
	free(path1);
  if (path2 != NULL)
	free(path2);
  
  int srcFd, destFd;
  /* kreira se bafer za prepisivanje podataka iz fajlova */
  static int bufferSize = 1<<13U;
  char* buffer = malloc(bufferSize);
  
  /* ukoliko alokacija bafera nije uspesna prijavljuje se greska */
  if (buffer == NULL) {
    perror("Buffer allocation failed");
    exit(EXIT_FAILURE);
  }
  
  /* otvaraju se fajlovi u odgovarajucim modovima */
  if ((destFd = open(destPath, O_RDWR)) == -1) {
    perror("Destination file open failed");
    exit(EXIT_FAILURE);
  }
  if ((srcFd = open(srcPath, O_RDONLY)) == -1) {
    perror("Source file open failed");
    exit(EXIT_FAILURE);
  }
  
  /* file offset se pozicionira na poziciju pos */
  if (lseek(destFd, (off_t)pos, SEEK_SET) == -1){
    perror("Offset positioning failed");
    exit(EXIT_FAILURE);
  }
  
  int readBytes = 0;
  /* bajtovi se citaju sve dok se ne dodje do kraja fajla */
  while((readBytes = read(srcFd, buffer, bufferSize)) > 0) {
    /* procitani bajtovi se upisusuju u drugi fajl */
    if (write(destFd, buffer, readBytes) != readBytes) {
      perror("write operation failed"); 
      exit(EXIT_FAILURE);
    }
  }
  /* ukoliko je doslo do greske prilikom citanja, prijavljuje se greska */
  if (readBytes != 0) {
    perror("read operation failed");
    exit(EXIT_FAILURE);
  }
  
  /* oslobadja se korisceni bafer */
  free(buffer);
  
  /* zatvaraju se korisceni fajl deskriptori */
  close(destFd);
  close(srcFd);
}

