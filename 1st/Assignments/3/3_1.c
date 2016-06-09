#include <stdio.h>
#include <stdlib.h>

void shell(int[], int);
void insertion(int[], int, int);
void swap(int *, int *);

int main(void) {
	int i, count=0;
	int tmp;
	int *a;
	char row[100], name[100];
	FILE *fp;
	
	printf("ファイル名：");
	scanf("%s", name);
	
	fp=fopen(name,"r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	
	a = (int *)malloc(sizeof(int)*100);
	tmp = 100;
	
	while(fgets(row, sizeof(row), fp) != NULL) {
		a[count] = atoi(row);
		count++;
		if (count == tmp) {
			a = (int *)realloc(a, sizeof(int)*(tmp+100));
			tmp += 100;
		}
	}
	
	fclose(fp);
	
	shell(a, count);
	
	printf("結果：\n");
	for (i=0; i<count; i++) {
		printf("%2d ", a[i]);
		if ((i+1)%20==0) printf("\n");
	}
	
	free(a);
}

void shell(int a[], int count)
{
	int i, h;
	for (i=0; i<100/9; i=3*i+1) h = i;
	while (h >= 1) {
		insertion(a, count, h);
		h = h/3;
	}
}

void insertion(int a[], int count, int h)
{
	int i, j, next;
	for(i=1; i<count; i+=h) {
		next = a[i];
		for(j=i; j>=1 && a[j-1]>next; j-=h) {
			swap(a+j, a+j-1);
		}
		a[j] = next;
	}
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}