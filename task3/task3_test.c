#include <stdio.h>
#include <stdlib.h>

long int length_buf = 10, length_lst = 2;

char **lst = NULL;

char *buf = NULL;

char **create_lst(void);

void 
print_lst(char *lst[]) 
{
	if (*lst == NULL) 
		return;
	printf("\"%s\"\n", *lst);
	lst++;
	print_lst(lst);
}

long int
length_lst_f(char *lst[])
{
	long int i = 0;
	while (lst[i])
		i++;
	return i;
}

void
free_all_elems_of_lst(char *lst[])
{
	for (long int i = 0; i < length_lst_f(lst); i++) {
		free(lst[i]);
	}
}

int
getsym(char *str)
{
	return *str;
}

int 
size(char *str)
{
	int n = 0;
	while (str[n]) {
		n++;
	}
	return n;
}

void 
error(void) 
{
	printf("Неудачное выделение памяти. Программа завершается...\n");
		
	//
	print_lst(lst);
	//освободить память
	free_all_elems_of_lst(lst);
	free(lst);
	free(buf);
	exit(0);
}

void
put_in_lst(char **lst[], char word[]) 
{
	long int i = 0;
	
	printf("in put_in_lst, before getting i;\n");
	while (i < length_lst && (*lst)[i] != NULL) {
		
		i++;
		printf("in while, i = %ld;\n", i);
	}
	
	printf("in put_in_lst, i = %ld;\n", i);
	
	//если массив переполнился
	if (i == length_lst) {
		length_lst += 8;
		(*lst) = realloc((*lst), length_lst * sizeof(char *));
		if (*lst == NULL) {
			error();
		}
	}
	
	printf("i = %ld; length(lst) = %ld;\n", i, length_lst);
	(*lst)[i] = word;
	
	//переставить указатель нулевой в конец
	i++;
	if (i == length_lst) {
		printf("making LIST bigger i = %ld;\n", i);
		length_lst += 8;
		(*lst) = realloc((*lst), length_lst * sizeof(char *));
		if (*lst == NULL) {
			error();
		}
		printf("made LIST bigger i = %ld; sizeof(lst) = %ld;\n", i, sizeof(*lst));
	}
	(*lst)[i] = NULL;
}

char **
create_lst(void)
{
	char **lst = calloc(length_lst, sizeof(char *));
	lst[0] = NULL;
	return lst;
}

void put_in_buf(char **buf, char letter) 
{
    long int i = 0;
    printf("sizeof(buf) = %ld;\n", length_buf);
    while (i < length_buf && (*buf)[i]) {
        i++;
        printf("increased i, where it = %ld;\n", i);
    }
    printf("put in buf, putting in index = %ld;\n", i);

    if (i == length_buf) {
		printf("NOT ENOUGH SPACE, i = %ld;\n", i);
		length_buf += 10;
		*buf = realloc(*buf, length_buf);
		if (*buf == NULL) {
			error();
		}
    }

    (*buf)[i] = letter;
    i++;

    if (i == length_buf) {
        printf("made BUF bigger i = %ld;\n", i);
        length_buf += 10;
        *buf = realloc(*buf, length_buf);
        if (*buf == NULL) {
			error();
		}
    }
    (*buf)[i] = '\0';
    printf("buf = \"%s\";\n", *buf);
}

void 
switch_elems(char *word1[], char *word2[])
{
	char *mid = *word2;
	*word2 = *word1;
	*word1 = mid;
}

/*
 * == 1, если меньше
 * == 2, если равно
 * == 0, если больше
 * если длина меньше, то она меньше
 */
char 
less_true(char word1[], char word2[])
{
	long int i = 0;
	while (word1[i] && word2[i]) {
		if (word1[i] > word2[i])
			return 0;
		else if (word1[i] < word2[i])
			return 1;
		i++;
	}
	if (word1[i] == word2[i])
			return 2;
	if (word1[i] == '\0' && word2[i] != '\0') {
		return 1;
	}
	if (word1[i] != '\0' && word2[i] == '\0') {
		return 0;
	}
	return 2;
}

void 
put_in_por(char *lst[])
{
	long int i, j;
	if (lst[0] == NULL)
		return;
	for (i = length_lst - 1; i >= 0 && lst[i]; i--) {
		for (j = 0; j < i && lst[i]; j++) {
			if (less_true(lst[j], lst[j + 1]) == 0) {
				printf("\"%s\" НЕ < \"%s\"; меняю местами...\n", lst[j], lst[j + 1]);
				switch_elems(&(lst[j]), &(lst[j + 1]));
			}
		}
	}
}

int
main(void)
{
	//счтываемая строка по 10 символов
	char str[11];
	
	//пустой массив слов
	lst = create_lst();
	
	//слово
	buf = malloc(10);
	if (buf == NULL) {
		error();
	}
	buf[0] = '\0';
	
	//количество символов в строке str
	int n = 0;
	
	//считывание по 10 символов
	while (fgets(str, 11, stdin) != NULL) {
		
		//удалить в конце строку ниже и перекомментирвоать вторую стркоу
		printf("\nstr = \"%s\";\nsizeof(str) = %d;\n", str, n = size(str));
		//n = size(str);
		
		//обработка каждого символа строки
		for (int i = 0; i < n; i++) {
			int c = getsym(str + i);
			printf("\nc = \'%c\' and i = %d;\n", c, i);
			
			if (c == EOF) {
				
			} else {
				
				c = (char) c;
				if (c == '\n' || c == ' ' || c == '\t' ||
					c == ';'  || c == '(' || c == ')'  ||
					c == '|'  || c == '&' ||
					c == '>'  || c == '<'
				) {
					if (c == ';'  || c == '(' || c == ')'  || c == '<') {
						
						// если это одинарная
						
						//если уже что-то есть в buf
						if (buf[0]) {
							put_in_lst(&lst, buf);
							printf("NOW LIST = ");
							char **first_in_lst = lst;
							print_lst(lst);
							lst = first_in_lst;
							printf("END\n");
							buf = malloc(2);
							if (buf == NULL) {
								error();
							}
						}
						
						
						length_buf = 2;
						buf[1] = '\0';
						buf[0] = c;
						put_in_lst(&lst, buf);
						printf("NOW LIST = ");
						char **first_in_lst = lst;
						print_lst(lst);
						lst = first_in_lst;
						printf("END\n");
						
						//новый buf
						buf = malloc(10);
						if (buf == NULL) {
							error();
						}
						length_buf = 10;
						buf[0] = '\0';
						printf("\nafter putting buf = \"%s\";\n", buf);
					} else if (c == '\n' || c == ' ' || c == '\t') {
							
						// если это пробелтный символ	
						put_in_lst(&lst, buf);
						printf("NOW LIST = ");
						char **first_in_lst = lst;
						print_lst(lst);
						lst = first_in_lst;
						printf("END\n");
						buf = malloc(10);
						if (buf == NULL) {
							error();
						}
						length_buf = 10;
						buf[0] = '\0';
					} else {
						
						//если это мб часть двойного спец символа
						
						//если это двойной спец символ уже встретился
						if (buf[0] == '|' || buf[0] == '&' || buf[0] == '>') {
							
							if (buf[0] ==  '|' && c == '|' ||
								buf[0] ==  '&' && c == '&' ||
								buf[0] ==  '>' && c == '>'
							) {
									
									//если это двойной символ
									buf[1] = c;
									buf[2] = '\0';
									
									//вставить в массив
									put_in_lst(&lst, buf);
									printf("NOW LIST = ");
									char **first_in_lst = lst;
									print_lst(lst);
									lst = first_in_lst;
									printf("END\n");
									
									//сделать новый buf
									buf = malloc(10);
									if (buf == NULL) {
										error();
									}
									length_buf = 10;
									buf[0] = '\0';
							} else {
									
									//одинарный
									buf[1] = '\0';
									
									//вставить в массив
									put_in_lst(&lst, buf);
									printf("NOW LIST = ");
									char **first_in_lst = lst;
									print_lst(lst);
									lst = first_in_lst;
									printf("END\n");
									
									//сделать новый buf
									buf = malloc(10);
									if (buf == NULL) {
										error();
									}
									length_buf = 10;
									buf[0] = c;
									buf[1] = '\0';
							}
							
							
						} else {
							
							//если это один спец символ встретился впервые
							
							if (buf[0]) {
								put_in_lst(&lst, buf);
								printf("NOW LIST = ");
								char **first_in_lst = lst;
								print_lst(lst);
								lst = first_in_lst;
								printf("END\n");
								buf = malloc(10);
								if (buf == NULL) {
									error();
								}
							}
							length_buf = 10;
							buf[0] = c;
							buf[1] = '\0';	
						}
					}
				} else {
					// если это не спецсиваолм или пробельный  то есть добавляем в буфер
					if (buf[0] == '|' || buf[0] == '&' || buf[0] == '>') {
						put_in_lst(&lst, buf);
						printf("NOW LIST = ");
						char **first_in_lst = lst;
						print_lst(lst);
						lst = first_in_lst;
						printf("END\n");
						buf = malloc(10);
						if (buf == NULL) {
							error();
						}
						length_buf = 10;
						buf[0] = '\0';
					}
					printf("\nright before putting, buf = \"%s\";\n", buf);
					put_in_buf(&buf, c);	
				}
			
			}
			
		}
	}
	if (buf[0]) {
		put_in_lst(&lst, buf);
		buf = malloc(1);
		if (buf == NULL) {
			error();
		}
		length_buf = 1;
		buf[0] = '\0';
	}
	length_lst = length_lst_f(lst);
	printf("\n===========\nIN THE END LIST with length = %ld:\n", length_lst);
	print_lst(lst);
	printf("===========\n");
	
	//переставить элементы в лексиграфиечсом порядке
	put_in_por(lst);
	//вывести
	printf("\n===========\nLIST AFTER with length = %ld:\n", length_lst);
	print_lst(lst);
	printf("===========\n");

	//освобождение памяти
	free_all_elems_of_lst(lst);
	free(lst);
	free(buf);
	return 0;
}
//освобоеждние памяти 
//удалить ненужные pritnf
