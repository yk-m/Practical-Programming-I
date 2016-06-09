﻿#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int Bubble(int[], int, int);
int Selection(int[], int, int);
int Insertion(int[], int, int);
int Shell(int[], int, int);
int shellInsertion(int[], int, int, int);
int quicksort(int[], int, int);
void swap(int *, int *);

int main(void) {
	int sort, reversed;
	int i, length=1000000, num;
	int a[length];
	double prTime;
	clock_t start,end;
	
	// srand((unsigned) time(NULL));
	for(i=0; i<length; i++) a[i] = rand();
	
	printf("| バブルソート : 1, 選択ソート : 2, 挿入ソート : 3, シェルソート : 4, クイックソート : 5 | ");
	scanf("%d", &sort);
	printf("| 降順 : 0, 昇順 : 1 | ");
	scanf("%d", &reversed);
	
	start = clock();
	if (sort == 1) {
		num = Bubble(a, length, reversed);
	} else if (sort == 2) {
		num = Selection(a, length, reversed);
	} else if (sort == 3) {
		num = Insertion(a, length, reversed);
	} else if (sort == 5) {
		num = quicksort(a, 0, length);
	} else {
		num = Shell(a, length, reversed);
	}
	end = clock();
	prTime = (double)(end-start)/CLOCKS_PER_SEC;
	
	printf("結果：\n");
	for (i=0; i<length; i++) {
		printf("%2d ", a[i]);
		if ((i+1)%20==0) printf("\n");
	}

	printf("\n\n");
	printf("CPUタイム %.7lfs\n交換回数 %d回\n", prTime, num);
}

// reversed=0 desc reversed=1 asc

int Bubble(int a[], int length, int reversed)
{
	int i, j, num=0;
	for(i=length-1; 0<i; i--) {
		for(j=0; j<i; j++) {
			if ((reversed && (a[j] < a[j+1])) || (!reversed && (a[j] > a[j+1]))) {
				swap(a+j, a+j+1);
				num++;
			}
		}
	}

	return num;
}

int Selection(int a[], int length, int reversed)
{
	int i, j, min, num=0;

	for(i=0; i<length; i++) {
		min = i;
		for(j=i+1; j<length; j++) {
			if ((reversed && (a[j] > a[min])) || (!reversed && (a[j] < a[min]))){
				min = j;
			}
		}
		swap(a+i, a+min);
		num++;
	}

	return num;
}

int Insertion(int a[], int length, int reversed)
{
	int i, j, next, num=0;

	for(i=1; i<length; i++) {
		next = a[i];
		for(j=i; j>=1 && (reversed)? a[j-1]<next : a[j-1]>next; j--) {
			a[j] = a[j-1];
			num++;
		}
		a[j] = next;
	}

	return num;
}

int Shell(int a[], int length, int reversed)
{
	int i, h, num=0;

	for (i=0; i<length; i=3*i+1) h = i;
	while (h > 0) {
		num += shellInsertion(a, length, reversed, h);
		h = h/3;
	}

	return num;
}

int shellInsertion(int a[], int length, int reversed, int h)
{
	int i, j, k, next, num=0;
	for(i=h; i<length; i++) {
		next = a[i];
		for(j=i; j>=h && ((!reversed && a[j-h]>next) || (reversed && a[j-h]<next)); j-=h) {
			a[j] = a[j-h];
			num++;
		}
		a[j] = next;
	}
	return num;
}

int quicksort(int a[], int left, int right)
{
	int start, end, pivot;
	int num;
	if (left >= right-1) return 0;
	start = left;
	end = right;
	pivot = a[left];
	while (1) {
		left++;
		while (a[left]  < pivot && left < right) left++;
		right--;
		while (a[right] > pivot && left < right) right--;
		if (left >= right) break;
		swap(a+left, a+right);
		num++;
	}
	swap(a+start, a+left-1);
	num ++;
	num += quicksort(a, start, left);
	num += quicksort(a, left, end);
	return num;
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// 結果（1000000個）
// 挿入ソート
// CPUタイム 871.0749020s
// 交換回数 782289923回

// シェルソート
// CPUタイム 0.4697100s
// 交換回数 48599913回