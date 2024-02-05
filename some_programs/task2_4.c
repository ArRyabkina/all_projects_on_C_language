#include <stdio.h>

const int LEN = 10000;

double str2double(char str[]) {
	double a = 0.0;
	int c;
	while ((c = *str) != '\0' && c >= '0' && c <= '9') {
		str++;
		a = a * 10 + c - '0';
	}
	if (c == '.') {
		unsigned long n = 1;
		str++;
		while ((c = *str) != '\0' && c >= '0' && c <= '9') {
			n *= 10;
			str++;
			a = a + (c - '0') * 1.0 / n;
		}
	}
	if (c == 'E' || c == 'e') {
		char znak_minus = 0;
		str++;
		unsigned long n = 0;
		if ((c = *str) != '\0' && (c == '-' || c == '+')) {
			if (c == '-') 
				znak_minus = 1;
			str++;
		}
		while ((c = *str) != '\0' && c == '0')
			str++;
		while ((c = *str) != '\0' && c >= '0' && c <= '9') {
				n = n * 10 + c - '0';
				str++;
		}
		if (znak_minus == 1) {
			for (unsigned long i = 0; i < n; i++)
				a = a / 10;
		} else {
			for (unsigned long i = 0; i < n; i++)
				a = a * 10;
		}
	}
	if (*str == 'F' || *str == 'f')
		return (float) a;
	return a;
}

int main(void) 
{	
	double a, x;
	char str[LEN];
	while (scanf("%s", str) == 1) {
		printf("%.10g\n", str2double(str));
	}
	return 0;
}
