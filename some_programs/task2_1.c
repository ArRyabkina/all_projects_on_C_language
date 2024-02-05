#include <stdio.h>

double x, e;

double abs_double(double x) 
{
	if (x < 0) 
		return -x;
	else 
		return x;
}

double Newton(double xi)
{
	if (abs_double(xi / 2 - x / xi / 2) - e >= 0) {
		return Newton(xi / 2 + x / xi / 2);
	} else {
		return xi / 2 + x / xi / 2;
	}
}

int main(void) 
{	
	scanf("%lf", &e);
	while (scanf("%lf", &x) == 1) {
		if (x >= -0.0) {
			printf("%.10g", Newton(1));
		}
	}
	return 0;
}
