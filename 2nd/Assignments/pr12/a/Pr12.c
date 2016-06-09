/* ナップザック問題（動的計画法による解法） */

#include<stdio.h>
#include<stdlib.h>

/* 配列size、valueはそれぞれ荷物の大きさと価値を表わしている
 * 同じ添え字同士が対応している(例：荷物0の大きさはsize[0]、価値はvalue[0]）。
 */

/* 荷物の大きさ */
int size[] = {2, 3, 5, 7, 9, 15};

/* 荷物の価値 */
int value[] = {2, 4, 7, 11, 14, 24};

/* 荷物の種類の数 */
#define AS (sizeof(size)/sizeof(size[0]))

/* ナップザックの大きさの上限 */
#define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
	int i,j;

	/* 現時点でナップザックに詰め込んだ荷物の価値の合計 */
	int total[MAX_M];

	/* 最後に選んだ荷物 */
	int choice[MAX_M];

	/* 荷物iを入れた時の価値の合計 */
	int repack_total;

	/* 配列をクリアしておく */
	for(i=0;i<=N;i++){
		total[i] = 0;
		choice[i] = -1;
	}

	/* 荷物 i = 0?AS までを考慮に入れる */
	for(i=0;i<AS;i++){
		/* 大きさj(=Nsize[i])のナップザックに対して、荷物を詰め込んでみる */
			/* もし荷物iを入れたとすると、価値の合計はいくらになるかを計算して、変数repack_totalに格納 */
			/* 荷物iを入れた方が(入れないより)価値が大きくなるのなら、荷物iを入れる */
		/* 配列total、choiceの中身を表示する */

        for(j = 0; j <= N; j++){
			repack_total = 0;
				
			printf("%d < %d\n",j, Nsize[i]);
			if( j < Nsize[i]) continue;

			repack_total = total[j - Nsize[i]] + Nvalue[i];

			if(total[j] < repack_total){
				total[j] = repack_total;
				choice[j] = i;
			}
		}

		printf("i = %d\n",i);
		printf("total  = ");
		for(j=0;j<=N;j++){
			printf("%2d ",total[j]);
		}
		printf("\n");
		printf("choice = ");
		for(j=0;j<=N;j++){
			printf("%2d ",choice[j]);
		}
		printf("\n");
	}

	/* どの荷物をナップザックに入れたかを表示する */
	for(i = N; choice[i] != -1; i -= Nsize[choice[i]]){
		printf("荷物 %d (価値%2d)を詰め込む\n", choice[i], Nvalue[choice[i]]);
		getchar();
	}
	printf("価値の合計 = %d",total[N]);
}

int main(int argc, char *argv[]){
	/* ナップザックの大きさ */
	int m;

	/* 引数の数が誤っていないか、ナップザックの大きさが上限を超えていないか
	 * 判定（適切な引数の数、もしくは値が設定されていない場合、再度入力を求める）
	 */
	if(argc != 2){
		printf("usage : filename num\n");
		return 0;
	}

	/* コマンド引数からナップザックの大きさを得る */
	m = atoi(argv[1]);

	if(m < 0 || MAX_M < m){
		printf("Not valid number. Please input 0-199\n");
		return 0;
	}
	printf("Size of knapsack is %d\n",m);

	DynamicProgramming(m,size,value);

	return 0;
}
