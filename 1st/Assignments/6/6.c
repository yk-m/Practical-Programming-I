#include <stdio.h>
#include <stdlib.h>

void heap(int[], int, int);
void swap(int *, int *);

int main(void) {
	int i, k, length=0, n, tmp;
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

	n = length;

	for (k=n-1; k>=0; k--) {
		heap(a, n, k);
	}
	while (n > 1) {
		swap(&a[0], &a[n-1]);
		n--;
		heap(a, n, 0);
	}

	printf("結果：\n");
	for (i=0; i<length; i++) {
		printf("%2d ", a[i]);
		if ((i+1)%20==0) printf("\n");
	}
}

void heap(int d[], int n, int idx)
{
	if (idx*2+2>=n) return;
	if (d[idx*2+1]< d[idx*2+2] && d[idx]<d[idx*2+2]) {
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
