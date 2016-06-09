#include <stdio.h>
#include <stdlib.h>

void binarySearch (int data[], int key, int start, int end);
int input(int *a, char name[], int tmp);

int main()
{
	int i, key,length=0, tmp = 10000000;
	int *a;
	char name[64];
	char row[64];
	FILE *fp;

	printf("ファイル名：");
	scanf("%s", name);

	a = (int *)malloc(sizeof(int)*tmp);

	fp=fopen(name,"r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	
	while(fgets(row, sizeof(row), fp) != NULL) {
		a[length] = atoi(row);
		length++;
		if (length == tmp) {
			tmp += 1000;
			a = (int *)realloc(a, sizeof(int)*tmp);
		}
	}
	
	fclose(fp);

	do {
		printf("探索する数：");
		scanf("%d", &key);
		binarySearch(a, key, 0, length-1);
	} while (key != 0);



	return 0;
}

void binarySearch (int data[], int key, int start, int end)
{
	int mid = (end + start) / 2;
	if      (data[mid]== key) printf("%d : %d番目\n", key, mid);
	else if (start >= end)    printf("該当なし\n");
	else if (data[mid] < key) binarySearch(data, key, mid+1, end);
	else if (data[mid] > key) binarySearch(data, key, start, mid-1);
}