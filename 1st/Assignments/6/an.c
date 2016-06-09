#include<stdio.h>
#include<stdlib.h>

#define FILE_NAME "/Users/yuka/SampleData/kadai-05-sample2.txt"

void heap(int d[],int n,int idx);
void swap(int *a,int *b);

int main()
{
	int k,n=0,d[1000000],tmp,size;
	FILE *fp;
	fp=fopen(FILE_NAME,"r");
	if(fp==NULL){
		printf("cannot open file\n");
		exit(1);
	}
	
	while(fscanf(fp,"%d",&d[n])!=EOF) n++;
	size=n;

	for(k=(n-1)/2;k>=0;k--){
		heap(d,n,k);
	}

	while(n>1){
		tmp=d[0];
		d[0]=d[n-1];
		d[n-1]=tmp;
		n--;
		heap(d,n,0);
	}

	for(k=0;k<size;k++){
		printf("%d\n",d[k]);
	}

	return 0;
}

void swap(int *a,int *b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

void heap(int d[],int n,int idx)
{
	if(idx*2+1 > n-1){
		return;
	}else if(idx*2+1 == n-1){
		if(d[idx] < d[idx*2+1]){
			swap(&d[idx],&d[idx*2+1]);
		}
		return;
	}else{
		if(d[idx] < d[idx*2+1]){
			swap(&d[idx],&d[idx*2+1]);
			heap(d,n,idx*2+1);
		}
		if(d[idx] < d[idx*2+2]){
			swap(&d[idx],&d[idx*2+2]);
			heap(d,n,idx*2+2);
		}
		return;
	}
	return;
}
