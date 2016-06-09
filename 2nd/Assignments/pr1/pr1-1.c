#include <stdio.h>
#include <stdlib.h>

/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 0  /* 1:通常版，  0:番兵版   */
#define LOOP   0  /* 1:ループ版，0:再帰版   */

#define N  1000000  /* 探索するレコード数 */ 

/* 線形探索 */
int l_search(int data[], int target)
{
	int i
	  , count = 0
	;

#if NORMAL   /* 通常版 */
	for ( i = 0; i < N; i++ )
		if ( target == data[i] )
			return i;
	return -1;
#else        /* 番兵版 */
	data[N-1] = target;
	i = 0;
	while (1) {
		if ( target == data[i] )
			break;
		i++;
	}
	if (i == N-1)
		return -1;
	return i;
#endif
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* クイックソート */
void quick(int data[], int left, int right)
{
	int start
	  , end
	  , pivot
	;

	if (left >= right-1)
		return;

	start = left;
	end = right;
	pivot = data[left];

	while (1) {
		left++;
		while (data[left]  < pivot && left < right)
			left++;
		right--;
		while (data[right] > pivot && left < right)
			right--;
		if (left >= right)
			break;
		swap(data+left, data+right);
	}

	swap(data+start, data+left-1);
	quick(data, start, left);
	quick(data, left, end);
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
	int mid;
#if LOOP
	while ( low <=high ) {
		mid = (low + high) / 2;
		if		(data[mid] > target)
			high = mid-1;
		else if (data[mid] < target)
			low  = mid+1;
		else if (data[mid] == target)
			return mid;
	}
#else
	if ( low > high )
		return -1;
	mid = (low + high) / 2;
	if		(data[mid] > target)
		return b_search(data, low, mid-1, target);
	else if (data[mid] < target)
		return b_search(data, mid+1, high, target);
	else if (data[mid] == target)
		return mid;
#endif
	return -1;
}

/* メイン */
int main(void)
{
	int a[N]
	  , i
	  , target
	  , work[N]
	  , index
	;

	for( i = 0; i < N; i++ )
		work[i] = rand() % N;
#if LINEAR
#else
	quick(work,0,N-1);
#endif
	for( target = N/2-25000; target < N/2+25000; target++ ) {
#if LINEAR
		index = l_search(work,target);
#else
		index = b_search(work,0,N-1,target);
#endif
		if (target > 520000 ) {
			printf("TARGET=%d: ", target);
			if ( index != -1 )
				printf("○\n");
			else
				printf("×\n");
		}
	}
	return 0;
}