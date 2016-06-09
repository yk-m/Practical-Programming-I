#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void msort(int*, int, int);
void merge(int*, int, int, int);
void swap (int*, int*);

int main(void) {
	int i, length=100000;
	int d[length];
	double prTime;
	for(i=0; i<length; i++) d[i] = rand()%1000;
	
	msort(d, 0, length);

	printf("結果：\n");
	for (i=0; i<length; i++) {
		printf("%2d\n", d[i]);
		// if ((i+1)%20==0) printf("\n");
	}
}

void msort(int d[], int left, int right)
{
	int m = (right+left)/2;
	if (left >= right) return;
	msort(d, left, m);
	msort(d, m+1, right);
	merge(d, left, right, m);
}

void merge(int d[], int left, int right, int m)
{
	int i
	  , length = right-left+1
	  , l=0
	  , r=m-left+1
	;

	int tmp[length];

	for (i=0; i<length; i++) {
		tmp[i] = d[left+i];
	}

	for (i=0; i<length; i++) {
		if      (length-1 < r)     { d[left+i] = tmp[l]; l++; }
		else if (m-left   < l)     { d[left+i] = tmp[r]; r++; }
		else if (tmp[r] <= tmp[l]) { d[left+i] = tmp[r]; r++; }
		else if (tmp[l] <= tmp[r]) { d[left+i] = tmp[l]; l++; }
	}
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}