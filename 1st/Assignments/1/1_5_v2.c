#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
	int num;
	double prTime;
} data_t;

data_t Bubble(int[], int, int);
data_t Selection(int[], int, int);
data_t Insertion(int[], int, int);
void interchange(int *, int *);

int main(void) {
	int i, count=0;
	int sort, order, size, tmp;
	int *a;
	char row[100], name[100];
	data_t d;
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
			d = Bubble(a, count, 1);
		} else {
			d = Bubble(a, count, 0);
		}
	} else if (sort == 2) {
		if (order == 1) {
			d = Selection(a, count, 1);
		} else {
			d = Selection(a, count, 0);
		}
	} else {
		if (order == 1) {
			d = Insertion(a, count, 1);
		} else {
			d = Insertion(a, count, 0);
		}
	}
	
	printf("結果：\n");
	for (i=0; i<count; i++) {
		printf("%2d ", a[i]);
		if ((i+1)%20==0) printf("\n");
	}
	printf("\n\n");
	printf("CPUタイム %.7lfs\n交換回数 %d回\n", d.prTime, d.num);
	free(a);
}

// fl=0 desc fl=1 asc

data_t Bubble(int a[], int count, int fl)
{
	int i, j, tmp;
	data_t d = {0,0};
	clock_t start,end;
	start = clock();
	for(i=count-1; 0<i; i--) {
		for(j=0; j<i; j++) {
			if ((fl && (a[j] < a[j+1])) || (!fl && (a[j] > a[j+1]))) {
				interchange(a+j, a+j+1);
				d.num++;
			}
		}
	}
	end = clock();
	d.prTime = (double)(end-start)/CLOCKS_PER_SEC;

	return d;
}

data_t Selection(int a[], int count, int fl)
{
	int i, j, tmp, min;
	data_t d = {0,0};
	clock_t start,end;
	start = clock();
	for(i=0; i<count; i++) {
		min = i;
		for(j=i+1; j<count; j++) {
			if ((fl && (a[j] > a[min])) || (!fl && (a[j] < a[min]))){
				min = j;
			}
		}
		interchange(a+i, a+min);
		d.num++;
	}
	end = clock();
	d.prTime = (double)(end-start)/CLOCKS_PER_SEC;

	return d;
}

data_t Insertion(int a[], int count, int fl)
{
	int i, j, tmp, next;
	data_t d = {0,0};
	clock_t start,end;
	start = clock();
	for(i=1; i<count; i++) {
		next = a[i];
		for(j=i; j>=1 && ((!fl && a[j-1]>next) || (fl && a[j-1]<next)); j--) {
			interchange(a+j, a+j-1);
			d.num++;
		}
		a[j] = next;
	}
	end = clock();
	d.prTime = (double)(end-start)/CLOCKS_PER_SEC;

	return d;
}

void interchange(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}