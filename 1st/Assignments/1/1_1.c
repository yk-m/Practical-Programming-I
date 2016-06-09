#include <stdio.h>

int main(void) {
	int i, j, tmp;
	int a[10];
	
	i = 0;
	while (i<10) {
		printf("%2dŒÂ–ÚF", i+1);
		scanf("%d", &tmp);
		a[i] = tmp;
		i++;
	}
	
	for(i=9; 0<i; i--) {
		for(j=0; j<i; j++) {
			if (a[j] > a[j+1]) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
	
	printf("Œ‹‰ÊF");
	for (i=0; i<10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}