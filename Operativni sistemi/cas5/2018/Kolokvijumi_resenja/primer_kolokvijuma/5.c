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
#include <string.h>
#include <limits.h>
#include <pwd.h>
#include <ftw.h>
#include <utime.h>

/* makro maskira neupotrebljene promenljive */
#define UNUSED(x)	((void)x)

/* makro definise granicnu velicinu fajla */
#define FILE_SIZE		(500)
/* makro definise granicni broj korisnika u vlasnickoj grupi fajla */
#define NO_OF_USERS		(3)

/* makro definise maksimalnu velicinu stringa */
#define MAX_STRING_SIZE (256)
/* makro za obradu gresaka */
  
/* poruka koja definise pravilno pozivanje programa */
static const char* os_Usage = "Usage: ./1 dirPath fileName";

/* funkcija kreira novi fajl na putanji filePath */
void osMakeFile(const char* filePath);
/* funkcija za ispitivanje velicine i tipa fajlova */
bool osIsFileSmaller(const char* filePath, intmax_t fSize, char** fType);
/* funkcija vraca ukupan broj korisnika sistema u vlasnickoj grupi fajla */
int osNumberOfUsersInGroup(const char* filePath);
/* funkcija nadovezuje fajlove od pozicije pos */
void osCatFileFromPos(const char* destPath, const char* srcPath, const off_t pos);
/* funkcija za procesiranje entiteta u direktorijumima */
int processFile(const char* fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

/* pokazivac na prosledjenu putanju do fajla */
static char* destFilePath = NULL;

int main(int argc, char** argv) {
  
  /* provera broja argumenata komandne linije */
  if (argc != 3) {
    
    perror(os_Usage);
    exit(EXIT_FAILURE);
  }
  
  /* proverava se da li je prosledjeni argument direktorijum */
  char* str = NULL;
  osIsFileSmaller(argv[1], FILE_SIZE, &str);
  if (strcmp(str, "Directory") != 0) {
    
    perror("Argument must be of type directory");
    exit(EXIT_FAILURE);
  }
  /* oslobadja se koriscena memorija */
  free(str);
  
  /* pamti se prosledjena putanja */
  destFilePath = argv[2];
  
  /* lokalna promenljiva za pamcenje zateknute vrednosti umaska */
  mode_t oldMask = 0;
  /* umask se postavlja na nula da bi se omogucilo jednostavno
   * kreiranje fajla sa proizvoljnim pravima pristupa 
   */
  oldMask = umask(0);
  
  /* kreira se fajl na prosledjenoj putanji */
  osMakeFile(destFilePath);
  
  /* vraca se zateknuta umask vrednost */ 
  umask(oldMask);
  
  /* rekurzivno se pretrazuje prosledjeni direktorijum i ispunjava se zadatak */
  if (nftw(argv[1], processFile, 50, 0) == -1){
    
    perror("Traversing directory failed");
    exit(EXIT_FAILURE);
  }
  
  /* postavlja se exit kod */
  exit(EXIT_SUCCESS);
}
/* funkcija za procesiranje entiteta u direktorijumima */
int processFile(const char* fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
  
  /* bafer obelezavamo kao nekorisceni arugment */
  UNUSED(ftwbuf);
  
  /* ako je u pitanju regularni fajl */
  if (typeflag == FTW_F) {
   
   /* ispitamo velicinu fajla */
   char *str = NULL;
   bool lowerThan = osIsFileSmaller(fpath, FILE_SIZE, &str);
   free(str);
   /* ako je fajl veci od zadate granice */
   if (!lowerThan) {
     
      /* odredimo broj korisnika u istoj vlasnickoj grupi fajla */
      int users = osNumberOfUsersInGroup(fpath);
      
      /* ako je broj korisnika veci od granice */
      if (users > NO_OF_USERS) {
	
	/* odredimo apsolutne putanje trenutnog fajla i fajla na koji vrsimo nadovezivanje */
	char* path1 = realpath(fpath, NULL);
	char* path2 = realpath(destFilePath, NULL);
	
	/* u fajlu na koji vrsimo nadovezivanje podesimo ofset na kraj fajla 
	 * i na taj nacin saznamo velicinu fajla
	 * prilikom otvaranja fajla koristimo apsolutnu putanju
	 */
	int fd = 0;
	if ((fd = open(path2, O_RDWR)) == -1) {
	  perror("File open failed");
	  exit(EXIT_FAILURE);
	}
	off_t pos = 0;
	if ((pos = lseek(fd, 0, SEEK_END)) == -1) {
	  perror("lseek failed");
	  exit(EXIT_FAILURE);
	}
	close(fd);
	
	/* ako su u pitanju isti fajlovi */
	if (strcmp(path1, path2) == 0) {
	 
	  /* oslobodimo alociranu memoriju */
	  free(path1);
	  free(path2);
	  
	  /* napustimo trenutni fajl i nastavimo rekurziju */
	  return 0;
	}
	
	/* nadovezemo trenutni fajl na fajl sa prosledjene putanje */	
	osCatFileFromPos(path2, fpath, pos);
	
	/* oslobodimo alociranu memoriju */
	free(path1);
	free(path2);
      }
      /* ako je broj korisnika manji od granice */
      else if (users < NO_OF_USERS) {
	
	struct utimbuf times;
	
	/* umanjimo vrednosti vremena pristupa  za tri dana */
	times.actime = sb->st_atime - 3*60*60*24;
	times.modtime = sb->st_mtime;
	
	/* zamenimo vremena u samom fajlu */
	if (utime(fpath, &times) == -1) {
	  perror("time fix failed");
	  exit(EXIT_FAILURE);
	}
      }
    }
  }
  
  /* postavimo povratnu vrednost */
  return 0;
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

/* funkcija za ispitivanje velicine i tipa fajlova */
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

/* funkcija nadovezuje fajlove od pozicije pos */
void osCatFileFromPos(const char* destPath, const char* srcPath, const off_t pos) {
 
  /* kreiraju se pune putanje fajlova */
  char* path1 = realpath(destPath, NULL);
  char* path2 = realpath(srcPath, NULL);
  
  /* ukoliko se radi o istom fajlu, prijavljuje se greska */
  if (strcmp(path1, path2) == 0) {
    perror("dest and src must be different");
    exit(EXIT_FAILURE);
  }
  /* oslobadja se koriscena memorija */
  free(path1);
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
    