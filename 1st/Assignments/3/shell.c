#include <stdio.h>

int main(void) {
	int length=0, tmp, i;
	int a[100];
	char row[100];
	FILE *fp;
	
	fp=fopen("kadai-01-3.txt","r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	while(fgets(row, sizeof(row), fp) != NULL) {
		a[length] = atoi(row);
		length++;
	}
	
	fclose(fp);
	
	while () {
	}
	
	printf("åãâ ÅF");
	for (i=0; i<length; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}