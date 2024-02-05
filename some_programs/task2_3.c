#include <stdio.h>

int rekurs(int n) {
	if (n == 0) {
		return 0;
	} 
	if (n == 1) {
		return 1;
	}
	return rekurs(n - 2) + rekurs(n - 1);
}

int main(void) {
	int x;
	while (scanf("%d", &x) == 1) {
		printf("рекурсией = %d;\nитеративной = ", rekurs(x));
		if (x == 0)
			printf("%d;\n", 0);
		else if (x == 1) 
			printf("%d;\n", 1);
		else {
			long long unsigned fib0 = 0, fib1 = 1;
			for (int i = 1; i < x; i++) {
				long long unsigned cur = fib1;
				fib1 += fib0;
				fib0 = cur;
			}
			printf("%lld;\n", fib1);
		}
	}
	return 0;
}
