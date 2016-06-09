#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void msort(int*, int, int);
void merge(int*, int, int, int);
void swap (int*, int*);

int main(void) {
	int i, length, tmp = 10000;
	int *a;
	char name[64];
	char row[64];
	char *find;
	FILE *fp;

	printf("ファイル名：");
	scanf("%s", name);
	
	fp=fopen(name,"r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	
	a = (int *)malloc(sizeof(int)*1000);
	tmp = 1000;
	
	while(fgets(row, sizeof(row), fp) != NULL) {
		a[length] = atoi(row);
		length++;
		if (length == tmp) {
			tmp += 1000;
			a = (int *)realloc(a, sizeof(int)*tmp);
		}
	}

	fclose(fp);

	msort(a, 0, length);

	printf("結果：\n");
	for (i=0; i<length; i++) {
		printf("%2d ", a[i]);
		if ((i+1)%20==0) printf("\n");
	}
}

void msort(int d[], int left, int right)
{
	int m = (right-1+left)/2;
	if (left >= right-1) return;
	msort(d, left, m);
	msort(d, m+1, right);
	merge(d, left, right, m);
}

void merge(int d[], int left, int right, int m)
{
	int i
	  , l=0
	  , r=m-left+1
	  , length = right-left+1
	;

	int *tmp;

	tmp = (int *)malloc(sizeof(int)*length);

	for (i=0; i<length; i++) {
		tmp[i] = d[left+i];
	}

	for (i=0; i<length; i++) {
		if      (length <= r)      { d[left+i] = tmp[l]; l++; }
		else if (m-left <  l)      { d[left+i] = tmp[r]; r++; }
		else if (tmp[r] <= tmp[l]) { d[left+i] = tmp[r]; r++; }
		else if (tmp[l] <= tmp[r]) { d[left+i] = tmp[l]; l++; }
	}

	free(tmp);
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}