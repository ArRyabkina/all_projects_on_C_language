#include <stdio.h>

double x;

double func(double a0, double an) {
	return a0 + x * an;
}

int main(void) 
{	
	double a, an, p = 0;
	if (scanf("%lf", &x) == 1) {
		if (scanf("%lf", &an) == 1) {
			p = an;
			while (scanf("%lf", &a) == 1) {
				p = func(a, p);
			}
		}
	}
	printf("%lf", p);
	return 0;
}
