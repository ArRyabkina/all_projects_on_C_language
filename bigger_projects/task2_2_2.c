#include <stdio.h>

const unsigned ARR_N = 10000;

double x;

double func(double a0, double an) {
	return a0 + x * an;
}

int main(void) 
{	
	double a, an, p = 0, arr[ARR_N];
	unsigned n = 0;
	if (scanf("%lf", &x) == 1) {
		if (scanf("%lf", &an) == 1) {
			p = an;
			while (scanf("%lf", &a) == 1) {
				p = func(a, p);
				arr[n] = a;
				n++;
			}
		}
	}
	printf("%lf;\n", p);
	if (n > 0) {
		p = arr[n - 1] * n;
		if (n > 1) {
			for (long i = n - 2; i >= 0; i--) {
				p = func(arr[i] * (i + 1), p);
			}	
		}
	} else 
		p = 0;
	printf("%lf", p);
	return 0;
}
