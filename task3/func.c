#include "func.h" 

long long unsigned length_buf = 10, length_lst = 8;

char *buf = NULL;

char **lst = NULL;

void (*old_sig)(int);

// Объявление прототипов функций модуля

void
sigint_f(int sig) 
{
	free_all_elems_of_lst(lst);
	free(lst);
	free(buf);
	signal(SIGINT, old_sig);
	printf("\nПрограмма завершается...\n");
	exit(0);
}

void 
print_lst(char *lst[]) 
{
	if (*lst == NULL) 
		return;
	printf("\"%s\"\n", *lst);
	lst++;
	print_lst(lst);
}

long long unsigned
length_lst_f(char *lst[])
{
	long int i = 0;
	while (ULLONG_MAX - ULLONG_MAX % 8 - 1 > i && lst[i])
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

/*
 * type == 0 - не выделился блок памяти
 * type == 1 - введен недопустимый символ
 * type == 2 - не вмещается в long long unsigned длина buf или массива слов
 */

void 
error(char type) 
{
	if (type == 0)
		printf("\nНеудачное выделение памяти.");
	else if (type == 1)
		printf("\nНеправильный ввод данных.");
	else if (type == 2)
		printf("\nСлишком много данных.");
	else
		printf("\nОшибка.");
	printf(" Программа завершается...\n");
	
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
	while (i < length_lst && (*lst)[i] != NULL) {
		i++;
	}
	
	//если массив переполнился
	if (i == length_lst) {
		length_lst += 8;
		if (0 >= length_lst || length_lst * sizeof(char *) <= 0) 
			error(2);
		(*lst) = realloc((*lst), length_lst * sizeof(char *));
		if (*lst == NULL) {
			error(0);
		}
	}
	(*lst)[i] = word;
	
	//переставить указатель нулевой в конец
	i++;
	if (i == length_lst) {
		length_lst += 8;
		if (0 >= length_lst || length_lst * sizeof(char *) <= 0) 
			error(2);
		(*lst) = realloc((*lst), length_lst * sizeof(char *));
		if (*lst == NULL) {
			error(0);
		}
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

void 
put_in_buf(char **buf, char letter) 
{
    long int i = 0;
    while (i < length_buf && (*buf)[i]) {
        i++;
    }

    if (i == length_buf) {
		length_buf += 10;
		if (length_buf <= 0)
			error(2);
		*buf = realloc(*buf, length_buf);
		if (*buf == NULL) {
			error(0);
		}
    }

    (*buf)[i] = letter;
    i++;

    if (i == length_buf) {
		
        length_buf += 10;
        if (length_buf <= 0)
			error(2);
        *buf = realloc(*buf, length_buf);
        if (*buf == NULL) {
			error(0);
		}
    }
    (*buf)[i] = '\0';
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
			if (less_true(lst[j], lst[j + 1]) != 1) {
				switch_elems(&(lst[j]), &(lst[j + 1]));
			}
		}
	}
}

