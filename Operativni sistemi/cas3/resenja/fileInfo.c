/* Program stampa informacije o fajlu.
 *
 * Primer poziva:
 * ./file_info test.txt
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <pwd.h>
#include <time.h>
#include <grp.h>

#include <errno.h>

#define MAX_SIZE (1024)

/* makro za obradu gresaka -> da ne bih stalno kucao if(...) */
#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			/*fprintf(stderr, "%s\n", userMsg);*/ \
			exit(EXIT_FAILURE); \
		}\
	} while (0)	

/* funkcija kreira string reprezentaciju osobina fajla */
void printFileInfo(const char* filePath, char** string);
/* funkcija pronalazi ime korisnika na osnovu njegovog numerickog ID-a */
char* getUserName(uid_t uid);
/* funkcija pronalazi ime grupe na osnovu njenog numerickog ID-a */
char* getGroupName(gid_t gid);

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	check_error(argc == 2, "./fileInfo path");
	
	/* string inicijaizovan nulom */
	char* string = NULL;
	/* inicijalizacija stringa */
	printFileInfo(argv[1], &string);
	/* stampanje informacija o fajlu */
	printf("File info:\n%s", string);
	/* oslobadjanje resursa */
	free(string);
	
	/* zavrsavanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}

/* funkcija kreira string reprezentaciju osobina fajla */
void printFileInfo(const char* filePath, char** string) {
	
	/* provera da li je string inicijalizovan nulom */
	errno = EINVAL;
	check_error(*string == NULL, "needs to be null initialized");
	errno = 0;
	
	/* citamo informacije o fajlu
	 * za to se uvek koristi stat sist poziv
	 */
	struct stat fInfo;
	check_error(stat(filePath, &fInfo) != -1, "stat failed");
	
	/* alociramo prostor za string */
	char* fInfoStr = malloc(MAX_SIZE);
	check_error(fInfoStr != NULL, "malloc failed");
	
	/* da se ne bismo zamlacivali sa time da li je string terminisan ili ne,
	 * na pocetku programa cemo ga eksplicitno inicijalizovati nulama
	 */
	
	// malloc + memset <=> calloc()
	memset(fInfoStr, 0, MAX_SIZE); 
	
	/* ternutni offset u strringu */
	int totalBytes = 0;
	/* upisujemo prava pristupa
	 * pretpostavljamo da korisnik ima sve
	 */
	totalBytes += 
		sprintf(fInfoStr + totalBytes, "%s ", "-rwxrwxrwx");
	
	/* otkrivamo tip fajla 
	 * BITNO:
	 * obratite paznju na makroe S_IF... i S_IS...
	 * sve su makroi -> moraju da se koriste bitovki operatori
	 */
	switch(fInfo.st_mode & S_IFMT) {
		
		case S_IFREG:
			fInfoStr[0] = '-';
			break;
		case S_IFDIR:
			fInfoStr[0] = 'd';
			break;
		case S_IFCHR:
			fInfoStr[0] = 'c';
			break;
		case S_IFBLK:
			fInfoStr[0] = 'b';
			break;
		case S_IFIFO:
			fInfoStr[0] = 'p';
			break;
		case S_IFSOCK:
			fInfoStr[0] = 's';
			break;
		case S_IFLNK:
			fInfoStr[0] = 'l';
			break;
		default:
			break;
	}
	
	/* gasimo prava pristupa koja korisnik ne poseduje */
	if (!(fInfo.st_mode & S_IRUSR))
		fInfoStr[1] = '-';
	if (!(fInfo.st_mode & S_IWUSR))
		fInfoStr[2] = '-';
	if (!(fInfo.st_mode & S_IXUSR))
		fInfoStr[3] = '-';
	
	if (!(fInfo.st_mode & S_IRGRP))
		fInfoStr[4] = '-';
	if (!(fInfo.st_mode & S_IWGRP))
		fInfoStr[5] = '-';
	if (!(fInfo.st_mode & S_IXGRP))
		fInfoStr[6] = '-';
		
	if (!(fInfo.st_mode & S_IROTH))
		fInfoStr[7] = '-';
	if (!(fInfo.st_mode & S_IWOTH))
		fInfoStr[8] = '-';
	if (!(fInfo.st_mode & S_IXOTH))
		fInfoStr[9] = '-';
	
	/* upisujemo velicinu fajla */
	totalBytes += sprintf(fInfoStr + totalBytes, "%jd ", (intmax_t)fInfo.st_size);
	
	/* otkrivamo ime vlasnika fajla na osnovu njegovog ID-a */
	char* userName = getUserName(fInfo.st_uid);
	totalBytes += sprintf(fInfoStr + totalBytes,"%s ", userName);
	free(userName);
	
	/* otkrivamo ime vlasnicke grupe fajla na osnovu njenog ID-a */
	char* grpName = getGroupName(fInfo.st_gid);
	totalBytes += sprintf(fInfoStr + totalBytes,"%s ", grpName);
	free(grpName);
	
	/* prebacujemo poslednje vreme modifikacije u ljudima citljiv oblik */
	char* strTime = ctime(&fInfo.st_mtime);
	/* nadovezujemo to na fajl */
	totalBytes += sprintf(fInfoStr + totalBytes, "%s", strTime);
	
	//printf("File info:\n%s", fInfoStr);
	
	//free(fInfoStr);
	
	/* inicijalizujemo argument funkcije */
	*string = fInfoStr;
}

/* funkcija pronalazi ime korisnika na osnovu njegovog numerickog ID-a */
char* getUserName(uid_t uid) {
	
	struct passwd* userInfo = getpwuid(uid);
	check_error(userInfo != NULL, "getpwuid failed");
	
	char* name = malloc(strlen(userInfo->pw_name) + 1);
	check_error(name != NULL, "malloc failed");
	
	strcpy(name, userInfo->pw_name);
	
	return name;
}

/* funkcija pronalazi ime grupe na osnovu njenog numerickog ID-a */
char* getGroupName(gid_t gid) {
	
	struct group* groupInfo = getgrgid(gid);
	check_error(groupInfo != NULL, "getgrgid failed");
	
	char* groupName = strdup(groupInfo->gr_name);
	check_error(groupName != NULL, "strdup failed");
	
	return groupName;
}
