#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void descBubble(int a[], int count);
void descSelection(int a[], int count);
void descInsertion(int a[], int count);
void ascBubble(int a[], int count);
void ascSelection(int a[], int count);
void ascInsertion(int a[], int count);
void interchange(int *a, int *b);

int main(void) {
	int i, count=0;
	int sort, order, size, tmp;
	int *a;
	double time;
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
	
	printf("| バブルソート : 1, 選択ソート : 2, 挿入ソート : 3 | ");
	scanf("%d", &sort);
	printf("| 昇順 : 1, 降順 : 2 | ");
	scanf("%d", &order);
	
	if (sort == 1) {
		if (order == 1) {
			ascBubble(a, count);
		} else {
			descBubble(a, count);
		}
	} else if (sort == 2) {
		if (order == 1) {
			ascSelection(a, count);
		} else {
			descSelection(a, count);
		}
	} else {
		if (order == 1) {
			ascInsertion(a, count);
		} else {
			descInsertion(a, count);
		}
	}
	
	/* ファイルに出力する */
	printf("結果：");
	for (i=0; i<count; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	
	free(a);
}

void descBubble(int a[], int count)
{
	int i, j, tmp;
	for(i=count-1; 0<i; i--) {
		for(j=0; j<i; j++) {
			if (a[j] > a[j+1]) {
				interchange(a+j, a+j+1);
			}
		}
	}
}
void ascBubble(int a[], int count)
{
	int i, j, tmp;
	for(i=count-1; 0<i; i--) {
		for(j=0; j<i; j++) {
			if (a[j] < a[j+1]) {
				interchange(a+j, a+j+1);
			}
		}
	}
}

void descSelection(int a[], int count)
{
	int i, j, tmp, min;
	for(i=0; i<count; i++) {
		min = i;
		for(j=i+1; j<count; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		interchange(a+i, a+min);
	}
}
void ascSelection(int a[], int count)
{
	int i, j, tmp, min;
	for(i=count-1; 0<=i; i--) {
		min = i;
		for(j=i; 0<=j; j--) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		interchange(a+i, a+min);
	}
}

void descInsertion(int a[], int count)
{
	int i, j, tmp, next;
	for(i=1; i<count; i++) {
		next = a[i];
		for(j=i; j>=1 && a[j-1]>next; j--) {
			interchange(a+j, a+j-1);
		}
		a[j] = next;
	}
}
void ascInsertion(int a[], int count)
{
	int i, j, tmp, next;
	for(i=count-2; 0<=i; i--) {
		next = a[i];
		for(j=i; j<count-1 && a[j+1]>next; j++) {
			interchange(a+j, a+j+1);
		}
		a[j] = next;
	}
}

void interchange(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
