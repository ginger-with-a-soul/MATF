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

#include <string.h>

/* makro maskira neupotrebljene promenljive */
#define UNUSED(x)	((void)x)

/* makro definise maksimalnu velicinu stringa */
#define MAX_STRING_SIZE (256)

/* poruka koja definise pravilno pozivanje programa */
static const char* os_Usage = "Usage: ./1 filePath fileSize";

/* funkcija za ispitivanje velicine i tipa fajlova */
bool osIsFileSmaller(const char* filePath, intmax_t fSize, char** fType);

int main(int argc, char** argv) {
  
  /* provera broja argumenata komandne linije */
  if (argc != 3) {
    perror(os_Usage);
    exit(EXIT_FAILURE);
  }
  
  /* pokazivac na string, inicijalizovan nulom */
  char* fType = NULL;
  /* konverzija maksimalne velicine fajla iz stringa u broj */
  long fSize = strtol(argv[2], 0, 10);
  /* ispitivanje velicine i tipa fajla */
  bool result = osIsFileSmaller(argv[1], fSize, &fType);
  /* stampanje informacija o fajlu */
  printf("%s %s\n", fType, result ? "true" : "false");
  /* dealokacija koriscene memorije */
  free(fType);
  
  /* postavlja se exit kod */
  exit(EXIT_SUCCESS);
}

bool osIsFileSmaller(const char* filePath, intmax_t fSize, char** fType) {
  
  /* errno se postavlja na vrednost moguce greske */
  errno = EINVAL;
  /* ispitivanje ulaznog argumenta */
  if (*fType != NULL) {
    perror("String must be NULL initialized");
    exit(EXIT_FAILURE);
  }
  /* resetovanje vrednosti errno promenljive */
  errno = 0;
  
  /* alociranje memorije za poruku o tipu fajla */
  char* ft = malloc(MAX_STRING_SIZE);
  /* provera uspesnosti alokacije */
  if (ft == NULL) {
    perror("String allocation failed");
    exit(EXIT_FAILURE);
  }
  /* azuriranje vrednosti pokazivaca na string */
  *fType = ft;
  
  /* dobijanje informacija o fajlu */
  struct stat fInfo;
  if (stat(filePath, &fInfo) == -1) {
    perror("File stat failed");
    exit(EXIT_FAILURE);
  }
  
  /* u zavisnoti od tipa fajla, u string se upisuje odgovarajuca
   * poruka
   */
  switch (fInfo.st_mode & S_IFMT) {
    
    case S_IFREG:
      strcpy(ft, "Regular");
      break;
    case S_IFDIR:
      strcpy(ft, "Directory");
      break;
    case S_IFLNK:
      strcpy(ft, "Symbolic link");
      break;
    case S_IFCHR:
      strcpy(ft, "Character specific");
      break;
    case S_IFBLK:
      strcpy(ft, "Block specific");
      break;
    case S_IFSOCK:
      strcpy(ft, "Socket");
      break;
    case S_IFIFO:
      strcpy(ft, "FIFO");
      break;
    default:
      perror("Unknown file format");
      exit(EXIT_FAILURE);
  }
  
  /* uporedjuje se velicina fajla sa unapred zadatom 
   * maksimalnom velicinom i formira se povratna vrednost 
   */
  return fInfo.st_size < fSize;
}
    