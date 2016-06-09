#include <stdio.h>
#include <stdlib.h>

void bin(int);

int main(void) {
	int n;
	scanf("%d", &n);
	bin(n);
	return 0;
}

void bin(int n)
{
	if (n == 0) { printf("%d", n%2); return; }
	bin(n/2);
	printf("%d", n%2);
}
