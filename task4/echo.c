#include <stdio.h>
#include <stdlib.h>

/*
 * == 1, если -e 
 * == 0, если -E
 */
char mode_e_on = 0;

/*
 * == 1, если есть -n 
 * == 0, иначе
 */
char mode_n_on = 0;

/*
 * == 3, если str == "-E"
 * == 2, если str == "-e"
 * == 1, если str == "-n"
 * == 0, иначе
 */
char
check_str(char *str) 
{
	if (str == NULL || str[0] == '\0')
		return 0;
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return 1;
	else if (str[0] == '-' && str[1] == 'e' && str[2] == '\0')
		return 2;
	else if (str[0] == '-' && str[1] == 'E' && str[2] == '\0')
		return 3;
	else 
		return 0;
}

void
fprintf_e_off(FILE *place, char *str) 
{
	if (str == NULL)
		return;
	char *cur = str;
	while (*cur) {
		fprintf(place, "%c", *cur);
		cur++;
	}
}

void
fprintf_e(FILE *place, char *str)
{
	if (str == NULL)
		return;
	char *first = str;
	
	while (*str) {
		
		if (*str == '\\') {
			if (str[1] == '\0') {
				str = first;
				return;
			} else if (str[1] == 'a') {
				
				// '\a'
				fprintf(place, "\a");
				str += 2;
				
			} else if (str[1] == 'b') {
				
				// '\b'
				fprintf(place, "\b");
				str += 2;
				
			} else if (str[1] == 'c') {
				
				// '\c'
				if (mode_n_on != 1) 
					fprintf(place, "\n");
				exit(0);
				
			} else if (str[1] == 'e') {
				
				// '\e'
				str += 2;
				if (*str) {
					str++;
				}
				
			} else if (str[1] == 'f') {
				
				// '\f'
				fprintf(place, "\f");
				str += 2;
				
			} else if (str[1] == 'n') {
				
				// '\n'
				fprintf(place, "\n");
				str += 2;
				
			} else if (str[1] == 'r') {
				
				// '\r'
				fprintf(place, "\r");
				str += 2;
			} else if (str[1] == 't') {
				
				// '\t'
				fprintf(place, "\t");
				str += 2;
				
			} else if (str[1] == 'v') {
				
				// '\v'
				fprintf(place, "\v");
				str += 2;
				
			} else if (str[1] == '\\') {
				
				// '\\'
				fprintf(place, "\\");
				str += 2;
				
			} else if (str[1] == '0') {
				if (str[2] <= '7' && str[2] >= '0') {
				
					// '\0nnn'
					int n8 = str[2] - '0';
					str += 1;
					if (str[2] <= '7' && str[2] >= '0') {
						n8 = n8 * 8 + str[2] - '0';
						str += 1;
						if (str[2] <= '7' && str[2] >= '0') {
							n8 = n8 * 8 + str[2] - '0';
							str += 1;
						}
					}
					fprintf(place, "%c", (char) n8);
				} 
				str += 2;   
				
			} else if (str[1] <= '7' && str[1] >= '0') {
				
				// '\nnn'
				int n8 = str[1] - '0';
				str += 1;
				if (str[1] <= '7' && str[1] >= '0') {
					n8 = n8 * 8 + str[1] - '0';
					str += 1;
					if (str[1] <= '7' && str[1] >= '0') {
						n8 = n8 * 8 + str[1] - '0';
						str += 1;
					}
				}
				fprintf(place, "%c", (char) n8);
				str += 1;  
			} else if (str[1] == 'x') {
				if (str[2] <= '7' && str[2] >= '0') {
				
					// '\xhh'
					int n8 = str[2] - '0';
					str += 1;
					if (str[2] <= '7' && str[2] >= '0') {
						n8 = n8 * 16 + str[2] - '0';
						str += 1;
					}
					fprintf(place, "%c", (char) n8);
				} 
				str += 2;   
			} else {
				fprintf(place, "%c", *str);
				str++;
			}
		} else {
			fprintf(place, "%c", *str);
			str++;
		}
	}
}

int
main(int argn, char **argv)
{
	if (argn == 1) {
		fprintf(stdout, "\n");
		return 0;
	}
	int j = 1;
	int check = (int) check_str(argv[1]);
	if (check == 1) {
		j = 2;
		mode_n_on = 1;
	} else if (check == 2) {
		j = 2;
		mode_e_on = 1;
	} else if (check == 3) {  
		j = 2;
		mode_e_on = 0;
	}
	for (;(check = (int) check_str(argv[j])) != 0; j++) {
		if (check == 1) 
			mode_n_on = 1;
		if (check == 2)
			mode_e_on = 1;
		if (check == 3)
			mode_e_on = 0;
	}
	argn--;
	int i = j;
	for (; i < argn; i++) {
		if (mode_e_on) {
			fprintf_e(stdout, argv[i]);
		} else 
			fprintf_e_off(stdout, argv[i]);
		fprintf(stdout, " ");
	}
	if (i >= argn) {
		if (mode_e_on == 1)
			fprintf_e(stdout, argv[argn]);
		else 
			fprintf_e_off(stdout, argv[argn]);
	}
	if (mode_n_on != 1) 
		fprintf(stdout, "\n");
	return 0;
}
