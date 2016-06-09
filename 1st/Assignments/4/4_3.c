#include <stdio.h>
#include <stdlib.h>

int add(int n);

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d\n", add(n));
	return 0;
}

int add(int n)
{
	if (n==1) return 1;
	return n + add(n-1);
}
