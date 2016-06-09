#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heap(int[], int, int);
void swap(int *, int *);

int main(void) {
	int sort, reversed;
	int i, k, length=99999, n;
	int d[length];
	double prTime;
	clock_t start,end;
	for(i=0; i<length; i++) d[i] = rand()%100000;
	
	n = length;

	start = clock();
	for (k=n-1; k>=0; k--) {
		heap(d, n, k);
	}
	while (n > 1) {
		swap(&d[0], &d[n-1]);
		n--;
		heap(d, n, 0);
	}
	end = clock();
	prTime = (double)(end-start)/CLOCKS_PER_SEC;

	printf("結果：\n");
	for (i=0; i<length; i++) {
		printf("%2d\n", d[i]);
		// if ((i+1)%20==0) printf("\n");
	}
	printf("CPUタイム %.7lfs\n", prTime);
}

void heap(int d[], int n, int idx)
{
	int child=idx*2+1;
	if (child>=n) return;
	if (child+1<n && d[child]<d[child+1]) {
		child++;
	}
	if (d[idx]<d[child]) {
		swap(&d[idx], &d[child]);
		heap(d, n, child);
	}

}
void heap_old(int d[], int n, int idx)
{
	if (idx*2+2>=n) return;
	if (d[idx*2+1]<d[idx*2+2] && d[idx]<d[idx*2+2]) {
		swap(&d[idx], &d[idx*2+2]);
		heap(d, n, idx*2+2);
	}
	if (idx*2+1<n && d[idx*2+1]>=d[idx*2+2] && d[idx]<d[idx*2+1]) {
		swap(&d[idx], &d[idx*2+1]);
		heap(d, n, idx*2+1);
	}

}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
