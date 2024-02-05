#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int dp = 0;

int
max_arr(int *arr)
{
	if (arr == NULL) {
		return 0;
	}
	int res = arr[0];
	int *first = arr;
	while (*arr) {
		if (arr[0] > res)
			res = arr[0];
		arr++;
	}
	arr = first;       
	while (res > 0) 
		res /= 10;
	return res;
}

int
main(int argn, char **argv)
{
	if (argn == 1) {
		int cur, pred = '\0';
		int amount_str = 0;
		int amount_letters = 0;
		int amount_words = 0;
		while ((cur = fgetc(stdin)) != EOF) {
			if (cur == '\n')
				amount_str++;
			if ((cur == ' ' ||
				cur == '\t' || 
				cur == '\n' ||
				cur == '\v' ||
				cur == '\f') &&
				(pred != ' ' &&
				pred != '\t' &&
				pred != '\n' &&
				pred != '\v' &&
				pred != '\f' &&
				pred != '\0')) {
				amount_words++;
			}
			amount_letters++;
			pred = cur;
		}
		if (amount_letters > 0 && amount_words == 0  && amount_str != 1) {
			amount_words++;
		}
		fprintf(stdout, "%7d %7d %7d\n", amount_str, amount_words, amount_letters);
	} else {
		int total_amount_str = 0;
		int total_amount_letters = 0;
		int total_amount_words = 0;
		int *array_of_s = calloc(sizeof(int), argn - 2);
		int *array_of_l = calloc(sizeof(int), argn - 2);
		int *array_of_w = calloc(sizeof(int), argn - 2);
		int amount_str;
		int amount_letters;
		int amount_words;
		for (int i = 1; i < argn; i++) {
			if ((dp = open(argv[i], O_RDONLY)) == -1) {
				array_of_s[i - 1] = -1;
			} else {
				int amount_str = 0;
				int amount_letters = 0;
				int amount_words = 0;
				char cur, pred = '\0';
				ssize_t bytesRead = 0;
				while((bytesRead = read(dp, &cur, 1)) > 0) {
					if (cur == '\n')
						amount_str++;
					if ((cur == ' ' ||
						cur == '\t' ||
						cur == '\n' ||
						cur == '\v' ||
						cur == '\f') && 
						(pred != ' ' &&
						pred != '\t' &&
						pred != '\n' &&
						pred != '\v' &&
						pred != '\f' &&
						pred != '\0')) {
						amount_words++;
					}
					amount_letters++;
					pred = cur;
				}
				if (bytesRead == -1) {
					return 1;
				}
				if (amount_letters > 0 && amount_words == 0 && amount_str != 1) {
					amount_words++;
				} 
				array_of_s[i - 1] = amount_str;
				array_of_w[i - 1] = amount_words;
				array_of_l[i - 1] = amount_letters;
				total_amount_str += amount_str;
				total_amount_letters += amount_letters;
				total_amount_words += amount_words;
				fprintf(stdout, "  %d %d %d %s\n", amount_str, amount_words, amount_letters, argv[1]);
				close(dp);
			}
		}
		int max_s = max_arr(array_of_s);
		fprintf(stdout, "  %d %d %d %s\n", amount_str, amount_words, amount_letters, argv[1]);
		int max_l = max_arr(array_of_l);
		int max_w = max_arr(array_of_w);
		printf("%d %d %d", max_s, max_l, max_w);
		if (argn == 2)
			fprintf(stdout, "  %d %d %d %s\n", amount_str, amount_words, amount_letters, argv[1]);
		else {
			for (int i = 1; i < argn; i++) {
				if (array_of_s[i - 1] != -1)
					fprintf(stdout, "  %*d  %*d %*d %s\n", 
							max_s, array_of_s[i - 1], 
							max_w, array_of_w[i - 1], 
							max_l, array_of_l[i - 1], 
							argv[i]);
				else
					fprintf(stdout, "wc: %s: Нет такого файла или каталога\n", argv[i]);
			}
			fprintf(stdout, "  %*d  %*d %*d %s\n", max_s, total_amount_str, max_w, total_amount_words, max_l, total_amount_letters, "итого");
		}                      
		free(array_of_s);
		free(array_of_l);
		free(array_of_w);
	}
	return 0;
}
