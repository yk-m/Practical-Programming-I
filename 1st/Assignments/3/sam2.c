#include <stdio.h>

int main () {
	int a = 5;
	int *b = &a;

	printf("%p\n", b);
	printf("こんにちは\n");
	return 0;
}