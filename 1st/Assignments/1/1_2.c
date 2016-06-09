#include <stdio.h>

int main(void) {
	int i, j, tmp, min;
	int a[10];
	
	i = 0;
	while (i<10) {
		printf("%2dŒÂ–ÚF", i+1);
		scanf("%d", &tmp);
		a[i] = tmp;
		i++;
	}
	
	for(i=0; i<10; i++) {
		min = i;
		for(j=i+1; j<10; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		tmp = a[i];
		a[i] = a[min];
		a[min] = tmp;
	}
	
	printf("Œ‹‰ÊF");
	for (i=0; i<10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}