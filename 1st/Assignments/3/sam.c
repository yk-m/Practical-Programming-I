#include <stdio.h>
#include <stdlib.h>


int main(void) {
	int h, max;
	for (h=0; h<100/9; h=3*h+1) max = h;
	printf("%d", max);
}

