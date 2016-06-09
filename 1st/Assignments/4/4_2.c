#include <stdio.h>
#include <stdlib.h>

int factorial(int n);

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d\n", factorial(n));
	return 0;
}

int factorial(int n)
{
	if (n==1) return 1;
	return n * factorial(n-1);
}
