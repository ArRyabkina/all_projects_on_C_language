#include "func.h"

int
main(void)
{
	old_sig = signal(SIGINT, sigint_f);
	
	//счтываемая строка по 10 символов
	char str[11];
	
	//пустой массив слов
	lst = create_lst();
	
	//слово
	buf = malloc(10);
	if (buf == NULL) {
		error(0);
	}
	buf[0] = '\0';
	
	//количество символов в строке str
	int n = 0;
	
	//считывание по 10 символов
	while (fgets(str, 11, stdin) != NULL) {
		
		n = size(str);
		
		//обработка каждого символа строки
		for (int i = 0; i < n; i++) {
			int c = getsym(str + i);
			
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
							buf = malloc(2);
							if (buf == NULL) {
								error(0);
							}
						}
						
						
						length_buf = 2;
						buf[1] = '\0';
						buf[0] = c;
						put_in_lst(&lst, buf);
						
						//новый buf
						buf = malloc(10);
						if (buf == NULL) {
							error(0);
						}
						length_buf = 10;
						buf[0] = '\0';
					} else if (c == '\n' || c == ' ' || c == '\t') {
							
						// если это пробелтный символ	
						if(buf[0] != '\0') {
							put_in_lst(&lst, buf);
							buf = malloc(10);
							if (buf == NULL) {
								error(0);
							}
							length_buf = 10;
							buf[0] = '\0';
						}
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
									
									//сделать новый buf
									buf = malloc(10);
									if (buf == NULL) {
										error(0);
									}
									length_buf = 10;
									buf[0] = '\0';
							} else {
									
									//одинарный
									buf[1] = '\0';
									
									//вставить в массив
									put_in_lst(&lst, buf);
									
									//сделать новый buf
									buf = malloc(10);
									if (buf == NULL) {
										error(0);
									}
									length_buf = 10;
									buf[0] = c;
									buf[1] = '\0';
							}
							
							
						} else {
							
							//если это один спец символ встретился впервые
							
							if (buf[0]) {
								put_in_lst(&lst, buf);
								buf = malloc(10);
								if (buf == NULL) {
									error(0);
								}
							}
							length_buf = 10;
							buf[0] = c;
							buf[1] = '\0';	
						}
					}
				} else if (c >= 'a' && c <= 'z' ||
						   c >= 'A' && c <= 'Z' ||
						   c >= '0' && c <= '9' ||
						   c == '$' || c == '_' || c == '/' || c == '.'
				) {
					
					// если это не спецсиваолм или пробельный  то есть добавляем в буфер
					if (buf[0] == '|' || buf[0] == '&' || buf[0] == '>') {
						put_in_lst(&lst, buf);
						buf = malloc(10);
						if (buf == NULL) {
							error(0);
						}
						length_buf = 10;
						buf[0] = '\0';
					}
					put_in_buf(&buf, c);	
				} else {
					
					//недопустимый символ
					error(1);
				}
			
			}
			
		}
	}
	if (buf[0]) {
		put_in_lst(&lst, buf);
		buf = malloc(1);
		if (buf == NULL) {
			error(0);
		}
		length_buf = 1;
		buf[0] = '\0';
	}
	length_lst = length_lst_f(lst);
	printf("\n======================\nLIST with length = %lld:\n======\n", length_lst);
	print_lst(lst);
	
	//переставить элементы в лексиграфиечсом порядке
	put_in_por(lst);
	
	//вывести
	printf("======================\nIN THE END LIST with length = %lld:\n======\n", length_lst);
	print_lst(lst);
	printf("======================\n");

	//освобождение памяти
	free_all_elems_of_lst(lst);
	free(lst);
	free(buf);
	return 0;
}
