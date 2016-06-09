#include <stdio.h>
#include <time.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 1  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   0  /* 1:���[�v�ŁC0:�ċA��   */

#define N  32700  /* �T�����郌�R�[�h�� */ 

void swap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

/* ���`�T�� */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* �ʏ�� */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* �ԕ��� */
    /* �������� */
    /* data�̈�ԍŌ�ɔԕ���ǉ����� */
    /* ���[�v�ɔ�r�����͕s�v�i�f�[�^���Ɍ����L�[�������Ă������Ă��Ō�ɔԕ��͌����邩��j */
    /* �݂������烋�[�v�𔲂��� */
    /* �ԕ������݂���Ȃ�������-1��Ԃ� */
    /* �f�[�^���݂�������break�����Ƃ��̓Y�����̒l��Ԃ� */
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

/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
    int mid;
#if LOOP 
    /* ���[�v�o�[�W���� */
    /* �������� */
    /* low <= high �̊Ԃ̓��[�v�ilow > high�Ȃ猩����Ȃ������j */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������� high �� mid-1 �� */
    /* data[mid] ��� target ���傫����� low �� mid+1 �� */
    /* data[mid] == target �������烋�[�v�𔲂��� */
    /* ���������Ȃ� mid ��Ԃ� */
    /* ������Ȃ������Ȃ� -1 ��Ԃ� */
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
    /* �ċA�o�[�W���� */
    /* �������� */
    /* low > high �Ȃ猩����Ȃ������Ƃ������Ƃ� -1 ��Ԃ� */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������ΑO�������ōċA */
    /* data[mid] ��� target ���傫����Ό㔼�����ōċA */
    /* data[mid] == target �������猩�������Ƃ������Ƃ� mid ��Ԃ� */

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

/* ���C�� */
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
            printf("��\n");
		}else
            printf("�~\n");
    }
	finish=clock();
	printf("%d\n",finish-start);
 
    return 0;
}
