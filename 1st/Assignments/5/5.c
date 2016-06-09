#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myquicksort(int[], int, int);
void quicksort(int[], int, int);
void swap(int *, int *);

int main(void) {
	int i, length=0, num, tmp;
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
	
	quicksort(a, 0, length);

	find = strstr(name, ".txt");
	strcpy(find, ".log");
	fp=fopen(name,"w");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}

	for (i=0; i<length; i++) {
		fprintf(fp,"%2d\n", a[i]);
	}
	fclose(fp);
}

// reversed=0 desc reversed=1 asc

void myquicksort(int a[], int left, int right)
{
	int start, end, pivot;
	if (left >= right-1) return;
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
	}
	swap(a+start, a+left-1);
	quicksort(a, start, left);
	quicksort(a, left, end);
}
void quicksort( int data[], int left, int right )
{
	int pvt
	  , l=left
	  , r=right-1
	  , tmp
	; 
	if( left == right ) return ;

	pvt = data[left];

	while( l < r ) {
		while(data[r]>pvt&&l<=r)r--;
		while(data[l]<pvt&&l<=r)l++;
		if(l>=r)break;
		tmp = data[r];
		data[r] = data[l];
		data[l] = tmp;
		r-- ;
		l++ ;
	}
	tmp = data[r];
	data[r] = data[l];
	data[l] = tmp;

	if( left < l-1 ) {
		quicksort( data, left, l-1 ) ;
	}
	if( l+1 < right ) {
		quicksort( data, l+1, right ) ;
	}
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
