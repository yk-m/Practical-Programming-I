#include <stdio.h>
#include <stdlib.h>

int fib(int n);

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d\n", fib(n));
	return 0;
}

int fib(int n)
{
	if (n<3) return 1;
	return fib(n-2) + fib(n-1);
}
