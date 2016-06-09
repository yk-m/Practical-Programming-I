#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i, j, tmp, next, count=0;
	int a[100];
	char row[100];
	FILE *fp;
	
	fp=fopen("kadai-01-3.txt","r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	while(fgets(row, sizeof(row), fp) != NULL) {
		a[count] = atoi(row);
		count++;
	}
	
	fclose(fp);
	
	for(i=1; i<count; i++) {
		next = a[i];
		for(j=i; j>=1 && a[j-1]>next; j--) {
			a[j] = a[j-1];
		}
		a[j] = next;
	}
	
	printf("結果：");
	for (i=0; i<count; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}