#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>


/*
 * >= 1, если n включен
 * == 0, иначе
 */
int n_on = 0;

/*
 * == 1, если этот текст явлется флагом -n 
 * == 0, иначе
 */
char
n_yes(char *str)
{
	if (str == NULL)
		return 0;
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return 1;
	return 0;
}

int
main(int argn, char **argv)
{
	for(int i = 1; i < argn; i++) {
		if(n_yes(argv[i])) {
			n_on++;
		}
	}
	
	int position = 0;
	
	if (argn - n_on == 1) {
		
		char name_new_file[] = "tempXXXXXX";
		int fd = mkstemp(name_new_file);
		if (fd == -1) {
			perror("mkstemp");
			return 1;
		}
		position++;
		
		//изменить права доступа
		mode_t permissions = 0666; 
		if (fchmod(fd, permissions) == -1) {
			perror("fchmod");
			return 1;
		}
		
		//считываение всего ввода и вывод полученног текста
		int cur;
		lseek(fd, 0, SEEK_SET);
		while((cur = fgetc(stdin)) != EOF) {
			if (cur != '\n') {
				write(fd, &cur, 1);
			} else {
				lseek(fd, 0, SEEK_SET);
				if (n_on > 0) 
					fprintf(stdout, "%6d  ", position);
				while (read(fd, &cur, 1) > 0) {
					fprintf(stdout, "%c", cur);
				}
				fprintf(stdout, "\n");
				position++;
				//опустошить файл и поставить указатель на начало файла
				truncate(name_new_file, 0);
				lseek(fd, 0, SEEK_SET);
			}
		}
		
		//удалить файл из ОП
		if (unlinkat(AT_FDCWD, name_new_file, AT_REMOVEDIR) == -1) {
			return 1;
		}
		close(fd);
	} else {
		for (int i = 1; i < argn; i++) {
			if (n_yes(argv[i]) == 0) {
				int fd = open(argv[i], O_RDONLY, 0666);
				if (fd == -1) {
					fprintf(stdout, "cat: %s: Нет такого файла или каталога\n", argv[i]);
				} else {
					int cur;
					position++;
					if (n_on > 0) 
						fprintf(stdout, "%6d  ", position);
					while (read(fd, &cur, 1) > 0) {
						fprintf(stdout, "%c", cur);
						if (cur == '\n') {
							if (n_on > 0 && read(fd, &cur, 1) > 0) {
								position++;
								fprintf(stdout, "%6d  ", position);
								lseek(fd, -1, SEEK_CUR);
							}
						}
					}
				}
				close(fd);
			}
		}
	}
	return 0;
}
