#ifndef FUNC_H // Защита от повторного включения
#define FUNC_H

#include "stdio.h" // Подключение заголовочных файлов, необходимых для функций модуля
#include "stdlib.h"
#include "signal.h"
#include "limits.h"

extern long long unsigned length_buf, length_lst;

extern char *buf;

extern char **lst;

extern void (*old_sig)(int);

// Объявление прототипов функций модуля

void sigint_f(int sig) ;

void print_lst(char *lst[]);

long long unsigned length_lst_f(char *lst[]);

void free_all_elems_of_lst(char *lst[]);

int getsym(char *str);

int size(char *str);

void error(char type) ;

void put_in_lst(char **lst[], char word[]);

char **create_lst(void);

void put_in_buf(char **buf, char letter);

void switch_elems(char *word1[], char *word2[]);

char less_true(char word1[], char word2[]);

void put_in_por(char *lst[]);

#endif
