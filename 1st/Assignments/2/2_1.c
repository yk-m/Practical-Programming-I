#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Shaker(int[], int);
void swap(int *, int *);

int main(void) {
	int i, length=0;
	int a[150];
	char row[100], name[100];
	FILE *fp;
	
	printf("ファイル名：");
	scanf("%s", name);
	
	fp=fopen(name,"r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	while(fgets(row, sizeof(row), fp) != NULL) {
		a[length] = atoi(row);
		length++;
	}

	fclose(fp);

	Shaker(a, length);
	
	printf("結果：");
	for (i=0; i<length; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Shaker(int a[], int length)
{
	int left, right, i, count=0, p;
	left = 0;
	right = length - 1;
	while(left <= right) {
		if (count % 2 == 0) {
			for (i=left; i<=right; i++) {
				if (a[i-1] >= a[i]) {
					swap(a+i, a+i-1);
					p = i-1;
				}
			}
			right = p;
		} else {
			for (i=right; left<i; i--) {
				if (a[i-1] >= a[i]) {
					swap(a+i, a+i-1);
					p = i;
				}
			}
			left = p;
		}
		count++;
	}
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}