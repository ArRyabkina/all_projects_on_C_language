#include <stdio.h>
int main(void) {
	printf("=====================\n");
	printf("N1\n\n");
	char prov_unsigned_char_true = 0;
	int n = 0;
	char c;
	
	/*
	checking for signed or unsigned form
	Проверка на знак  
	*/
	c = 0;
	c--;
	if (c < 0) {
		
		/*
		for signed
		для знаковых
		*/
	} else {
		
		/*
		for unsigned
		для беззнаковых
		*/
		prov_unsigned_char_true = 1;
	}
	
	/*
	to take from bit to byte
	*/
	char short_n = sizeof(short),
		 int_n = sizeof(int),
		 long_n = sizeof(long),
		 float_n = sizeof(float), 
		 double_n = sizeof(double),
		 long_double_n = sizeof(long double);
	printf("short = %d байт\nint = %d байт\nlong = %d байт\n", 
		   short_n, 
		   int_n,
		   long_n);
	printf("float = %d байт\ndouble = %d байт\nlong double = %d байт\n", 
		   float_n, 
		   double_n,
		   long_double_n);
	printf("=====================\n");
	printf("N2\n\n");
	if (prov_unsigned_char_true == 0)
		printf("signed char\n");
	else 
		printf("unsigned char\n");
	printf("=====================\n");
	return 0;
}
