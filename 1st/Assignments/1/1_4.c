#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Bubble(int[], int, int);
void Selection(int[], int, int);
void Insertion(int[], int, int, int);
void swap(int *, int *);

int main(void) {
	int i, length=0, num;
	int sort, reversed;
	int *a, tmp;
	char row[100], name[100];
	char *find;
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
		a[length] = atoi(row);
		length++;
		if (length == tmp) {
			a = (int *)realloc(a, sizeof(int)*(tmp+100));
			tmp += 100;
		}
	}
	
	fclose(fp);
	
	printf("| バブルソート : 1, 選択ソート : 2, 挿入ソート : 3 | ");
	scanf("%d", &sort);
	printf("| 昇順 : 1, 降順 : 2 | ");
	scanf("%d", &reversed);
	
	if (sort == 1) {
		if (reversed == 1) {
			Bubble(a, length, 1);
		} else {
			Bubble(a, length, 0);
		}
	} else if (sort == 2) {
		if (reversed == 1) {
			Selection(a, length, 1);
		} else {
			Selection(a, length, 0);
		}
	} else if (sort == 3) {
		if (reversed == 1) {
			Insertion(a, length, 1, 1);
		} else {
			Insertion(a, length, 0, 1);
		}
	}
	
	find = strstr(name, ".txt");
	strcpy(find, ".log");
	fp=fopen(name,"w");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}

	for (i=0; i<length; i++) {
		fprintf(fp,"%2d ", a[i]);
		if ((i+1)%20==0) fprintf(fp,"\n");
	}
	fclose(fp);
}

// reversed=0 desc reversed=1 asc

void Bubble(int a[], int length, int reversed)
{
	int i, j;
	for(i=length-1; 0<i; i--) {
		for(j=0; j<i; j++) {
			if ((reversed && (a[j] < a[j+1])) || (!reversed && (a[j] > a[j+1]))) {
				swap(a+j, a+j+1);
			}
		}
	}
}

void Selection(int a[], int length, int reversed)
{
	int i, j, min;

	for(i=0; i<length; i++) {
		min = i;
		for(j=i+1; j<length; j++) {
			if ((reversed && (a[j] > a[min])) || (!reversed && (a[j] < a[min]))){
				min = j;
			}
		}
		swap(a+i, a+min);
	}
}

void Insertion(int a[], int length, int reversed, int h)
{
	int i, j, k, next;
	for(i=h; i<length; i++) {
		next = a[i];
		for(j=i; j>=h && ((!reversed && a[j-h]>next) || (reversed && a[j-h]<next)); j-=h) {
			a[j] = a[j-h];
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