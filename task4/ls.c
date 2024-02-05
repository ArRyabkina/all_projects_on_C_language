#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <locale.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

char flag_r = 0;
char flag_l = 0;
char flag_g = 0; 

void print_dir(char *dir);
void all_dir(char *dirPath);
void printFileInfo(const char *str, const char *filename, int width);
char flag_f(char *str);
int max_arr(int *arr);

//напечатать все прямые файлы каталога dir
void
print_dir(char *dir)
{
	
	if (dir == NULL) 
		return;
	struct dirent **namelist;
	
	//для правильной сортировки в scandir с помощью alphasort
	setlocale(LC_COLLATE, "");
	
	//получение количества файлов и списка всех прямых файлов
    int count = scandir(dir, &namelist, NULL, alphasort);
    if (count == -1) {
        perror("scandir");
        exit(1);
    }
    
	off_t totalSize = 0;
	
	int totalBlocks = 0;
    
    for (int i = 0; i < count; i++) {
		
		if (namelist[i]->d_name[0] != '.' && namelist[i]->d_name[1] != '\0' ||
			namelist[i]->d_name[0] != '.' && namelist[i]->d_name[1] != '.' &&
			namelist[i]->d_name[2] != '\0') {
			char entryPath[1024];
			snprintf(entryPath, sizeof(entryPath), "%s/%s", dir, namelist[i]->d_name);
			
			//получить инфу о файле по относительному имени dir 
			struct stat fileStat;
			if (stat(entryPath, &fileStat) == -1) {
				perror("stat");
				continue;
			}
			
			//сумамарный размер всех файлов
			totalSize += fileStat.st_size;
			totalBlocks += fileStat.st_blocks;
		}
	}
	
	if (flag_l || flag_g)
		printf("итого %d\n", totalBlocks / 2);
	
	long long number = (long long) totalSize;
	int width = 0;
	while(number > 0) {
		number /= 10;
		width++;
	}
    
    //печатание всего списка
    count--;
    for (int i = 0; i < count; i++) {
		if (namelist[i]->d_name[0] != '.' && namelist[i]->d_name[1] != '\0' ||
			namelist[i]->d_name[0] != '.' && namelist[i]->d_name[1] != '.' &&
			namelist[i]->d_name[2] != '\0') {
			if (flag_l || flag_g) {
				char entryPath[1024];
				snprintf(entryPath, sizeof(entryPath), "%s/%s", dir, namelist[i]->d_name);
				printFileInfo(entryPath, namelist[i]->d_name, width);
				printf("\n");
			} else 
				printf("%s  ", namelist[i]->d_name);
			free(namelist[i]);
		}
    }
    if (namelist[count]->d_name[0] != '.' && namelist[count]->d_name[1] != '\0' ||
		namelist[count]->d_name[0] != '.' && namelist[count]->d_name[1] != '.' &&
		namelist[count]->d_name[2] != '\0') {
		if (flag_l || flag_g) {
			char entryPath[1024];
			snprintf(entryPath, sizeof(entryPath), "%s/%s", dir, namelist[count]->d_name);
			printFileInfo(entryPath, namelist[count]->d_name, width);
		} else
			printf("%s  ", namelist[count]->d_name);
		free(namelist[count]);
	}
    fprintf(stdout, "\n");
    free(namelist);
}

//напечатать все каталоги и файлы данного каталога для флага -R
void
all_dir(char *dirPath)
{
    struct stat entryStat;
    struct dirent **namelist;
	
	//открыть каталог с именем dirPath и получить список его прямых подкаталогов и файлов
	DIR *dir = opendir(dirPath);
	if (!dir) {
        perror("opendir");
        exit(1);
    }
    
    // получение количества файлов и списка всех файлов и каталогов
	int count = scandir(dirPath, &namelist, NULL, alphasort);
	if (count == -1) {
		perror("scandir");
		exit(1);
	}
    
	//обходим весь полученный список от opendir пока не будет конец списка
    for (int i = 0; i < count; i++) {
		
		// пропускаем записи, которые начинаются с точки, то есть скрытые каталоги
		if (namelist[i]->d_name[0] == '.') {
			continue;
		}
        char entryPath[1024];
        snprintf(entryPath, sizeof(entryPath), "%s/%s", dirPath, namelist[i]->d_name);

		//получить инфу о каталоге или файле по относительному имени entryPath 
        if (stat(entryPath, &entryStat) == -1) {
            perror("stat");
            continue;
        }
        
        //проверка, является ли имя entryPath каталогом
        if (S_ISDIR(entryStat.st_mode)) {
			
			// Исключаем родительский каталоги
			if (strcmp(namelist[i]->d_name, "..") == 0 || strcmp(namelist[i]->d_name, ".") == 0) {
				continue;
			}
				
			//печатаем название относительного имени каталога
			printf("\n%s:\n",entryPath);
				
			//печатаем все файлы текущего каталога 
			print_dir(entryPath);

			// Рекурсивно обходим подкаталоги
			all_dir(entryPath);
		}
        free(namelist[i]);
    }
    closedir(dir);
    free(namelist);
}

/*
 * == 1 -R
 * == 2 -l
 * == 3 -g
 * == 0, иначе
 */
char
flag_f(char *str)
{
	if (str == NULL)
		return 0;
	if (str[0] == '-' && str[1] == 'R' && str[2] == '\0')
		return 1;
	if (str[0] == '-' && str[1] == 'l' && str[2] == '\0')
		return 2;
	if (str[0] == '-' && str[1] == 'g' && str[2] == '\0')
		return 3;
	return 0;
}

void 
printFileInfo(const char *str, const char *filename, int width) 
{
	//получить инфу о файле по относительному имени str 
    struct stat fileStat;
    if (stat(str, &fileStat) == -1) {
        printf("stat:");
        return;
    }

	//получить имя пользователя 
    struct passwd *pw = getpwuid(fileStat.st_uid);
    if (pw == NULL) {
        perror("getpwuid");
        return;
    }
    
	//получить имя группы владельца
    struct group *grp = getgrgid(fileStat.st_gid);
    if (grp == NULL) {
        perror("getgrgid");
        return;
    }

	//права доступа
    char permissions[11];
    permissions[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
    permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

	//время
    char timeString[80];
    strftime(timeString, sizeof(timeString), "%b %d %H:%M", localtime(&fileStat.st_mtime));
    
	if (flag_g) {
		printf("%s %ld %s %*lld %s %s", permissions, fileStat.st_nlink, pw->pw_name, width, (long long)fileStat.st_size, timeString, filename);
		return;
	}
	printf("%s %ld %s %s %*lld %s %s", permissions, fileStat.st_nlink, pw->pw_name, grp->gr_name, width, (long long)fileStat.st_size, timeString, filename);
}

int 
main(int argn, char **argv)
{
    if (argn == 1) {
		print_dir(".");
	} else {
		
		//проверить все введеные флаги
		for (int i = 1; i < argn; i++) {
			char flag_res = flag_f(argv[i]);
			if (flag_res == 1) {
				flag_r = 1;
			} else if (flag_res == 2) {
				flag_l = 1;
			} else if (flag_res == 3) {
				flag_g = 1;
			} else {
				printf(".\n");
				break;
			}
		}
		if (flag_r) {
			printf(".:\n");
			print_dir(".");
			all_dir(".");
		} else if (flag_l || flag_g) {
			print_dir(".");
		}
	}
	return 0;
}
