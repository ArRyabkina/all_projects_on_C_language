#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int
main(int argn, char **argv)
{
	if (argn == 1) {
		fprintf(stdout, "cp: пропущен операнд, задающий файл\nПо команде «cp --help» можно получить дополнительную информацию.\n");
	} else if (argn == 2) {
		fprintf(stdout, "cp: после '%s' пропущен операнд, задающий целевой файл\nПо команде «cp --help» можно получить дополнительную информацию.\n", 
				argv[1]);
	} else if (argn == 3) {
		struct stat file_info;
		if (stat(argv[1], &file_info) == -1) {
			perror("Ошибка при получении информации о файле");
			return 1;
		}
		if (S_ISDIR(file_info.st_mode)) {
			
			//argv[1] - директория
			printf("cp: не указан -r; пропускается каталог '%s'\n", argv[1]);
		} else {
			
			//argv[2] - файл в который копируется 
			int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			char *new_file = NULL;
			
			//если второй файл оказался существующим каталогом
			if (fd2 == -1) {
				long long unsigned i = 0;
				long long unsigned j = 0;
				
				//i - количество символов относительного имени файла в который копируется
				while (argv[2][i]) {
					i++;
				}
				
				//j - количество символов относительного имени файла из которого копируется
				while (argv[1][j]) {
					j++;
				}
				
				//new_file - файл с именем argv[1] в каталоге argv[2]
				new_file = malloc(i + j + 2);
				i = 0;
				while (argv[2][i]) {
					new_file[i] = argv[2][i];
					i++;
				}
				new_file[i] = '/';
				j = 0;
				while (argv[1][j]) {
					new_file[i + j + 1] = argv[1][j];
					j++;
				}
				new_file[i + j + 1] = '\0';
				
				fd2 = open(new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd2 == -1) {
					printf("cp: не удалось выполнить stat для '%s': Нет такого файла или каталога\n", new_file);
					return 1;
					
				}
			}
			
			//открыть на чтение первый файл
			int fd1 = open(argv[1], O_RDONLY);
			if (fd1 == -1) {
				printf("cp: не удалось выполнить stat для '%s': Нет такого файла или каталога\n", argv[1]);
				return 1;
			}
			
			//копирование всех символов файла 1
			int cur;
			while (read(fd1, &cur, 1) > 0) {
				if (write(fd2, &cur, 1) <= 0) {
					return 1;
				}
			}
			close(fd1);
			close(fd2);
			if (new_file)
				free(new_file);
		}
	} else {
		struct stat file_info;
		if (stat(argv[argn - 1], &file_info) == -1) {
			perror("Ошибка при получении информации о файле");
			return 1;
		}
		if (S_ISDIR(file_info.st_mode)) {
			//последнее - директория
			
			//копиуем каталог в начало названия новых файлов
			long long unsigned i = 0;
			argn -= 1;
			while (argv[argn][i]) {
				i++;
			}
			char *new_file = malloc(i + 1);
			if (new_file == NULL) {
				return 1;
			}
			i = 0;
			while (argv[argn][i]) {
				new_file[i] = argv[argn][i];
				i++;
			}
			if (new_file[i - 1] != '/') {
				new_file[i] = '/';
			} else {
				i--;
			}
			new_file[i + 1] = '\0'; 
			
			for (int k = 1; k < argn; k++) {
				
				//fd2 - куда копируем
				
				//поставить j на место, откуда будем считывать название нового файла
				long long unsigned j = 0, i1;
				while (argv[k][j]) {
					j++;
				}
				
				while (j > 0 && argv[k][j] != '/') {
					j--;
				}
				if (argv[k][j] == '/') {
					j++;
					if (argv[k][j] == '\0') {
						j -= 2;
					}
					while (j > 0 && argv[k][j] != '/') {
						j--;
					}
					if (argv[k][j] == '/') {
						j++;
					}
				}
				i1 = j;
				while (argv[k][i1]) {
					i1++;
				}
				
				//расширение длины нового файла  
				i1 -= j;
				new_file = realloc(new_file, i + i1 + 2);
				
				//копирование всех букв из названия (без каталога) нового файла
				i1 = j;
				while (argv[k][j]) {
					new_file[i + j - i1 + 1] = argv[k][j];
					j++;
				}
				new_file[i + j - i1 + 1] = '\0';
				
				//recreate o create newfile
				int fd2 = open(new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd2 == -1) {
					printf("cp: не удалось выполнить stat для '%s': Нет такого файла или каталога\n", new_file);
				}
				
				//fd1 - откуда копируем
				int fd1 = open(argv[k], O_RDONLY);
				if (fd1 == -1) {
					printf("cp: не удалось выполнить stat для '%s': Нет такого файла или каталога\n", argv[1]);
				}

				int cur;
				while (read(fd1, &cur, 1) > 0) {
					if (write(fd2, &cur, 1) <= 0) {
						return 1;
					}
				}
				close(fd1);
				close(fd2);
				
			}
			free(new_file);
		} else {
			printf("cp: указанная цель '%s' не является каталогом\n", argv[argn - 1]);
		}
	}
	return 0;
}
