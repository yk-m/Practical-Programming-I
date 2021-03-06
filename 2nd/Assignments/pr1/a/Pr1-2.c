#include <stdio.h>
#include <time.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 1  /* 1:通常版，  0:番兵版   */
#define LOOP   0  /* 1:ループ版，0:再帰版   */

#define N  32700  /* 探索するレコード数 */ 

void swap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* 番兵版 */
    /* 実装せよ */
    /* dataの一番最後に番兵を追加する */
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
    data[N-1]=target;
    /*while(1){ 
		if(data[count++]==target) break;
	}*/
	while(data[++count]!=target);
    return (count==N-1)?-1:count;

#endif
}

void quick(int d[],int a,int b)
{
	int pivot,a_=a,b_=b;

	if(a>=b){
		return;
	}
	
	pivot=d[a];

	while(1){
		while(d[a]<pivot) a++;
		while(d[b]>pivot) b--;
		if(a>=b) break;
		swap(&d[a],&d[b]);
		a++;
		b--;
	}
	
	quick(d,a_,a-1);
	
	quick(d,b+1,b_);
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
    int mid;
#if LOOP 
    /* ループバージョン */
    /* 実装せよ */
    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ high を mid-1 に */
    /* data[mid] より target が大きければ low を mid+1 に */
    /* data[mid] == target だったらループを抜ける */
    /* 見つかったなら mid を返す */
    /* 見つからなかったなら -1 を返す */
    while(low<=high){
	    mid=(low+high)/2;
		if(data[mid]==target){
			return mid;
		}else if(data[mid]<target){
			low=mid+1;
		}else{
			high=mid-1;
		}
    }
    return -1;

#else
    /* 再帰バージョン */
    /* 実装せよ */
    /* low > high なら見つからなかったということで -1 を返す */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ前半部分で再帰 */
    /* data[mid] より target が大きければ後半部分で再帰 */
    /* data[mid] == target だったら見つかったということで mid を返す */

    if(low>high) return -1;

    mid=(low+high)/2;
    if(data[mid]>target){
	    return b_search(data,low,mid-1,target);
    }else if(data[mid]<target){
	    return b_search(data,mid+1,high,target);
    }else{
	    return mid;
    }
#endif
}

/* メイン */
int main(void)
{
    int i, target, work[N], index;
	clock_t start,finish;
    for( i = 0; i < N; i++ ) work[i] = rand() % N;
	start=clock();
#if LINEAR
#else
    quick(work,0,N-1);
#endif
    for( target = N/2-5000; target < N/2+5000; target++ ) {
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 ){
            printf("○\n");
		}else
            printf("×\n");
    }
	finish=clock();
	printf("%d\n",finish-start);
 
    return 0;
}
