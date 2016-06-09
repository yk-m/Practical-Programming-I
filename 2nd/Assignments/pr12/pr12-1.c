#include <stdio.h>
#include <stdlib.h>

/* 配列size、valueはそれぞれ荷物の大きさと価値を表わしている
 * 同じ添え字同士が対応している(例：荷物0の大きさはsize[0]、価値はvalue[0]）。
 */

/* 荷物の大きさ */
	int size[]  = { 2, 3, 5, 7, 9, 15 };
	
/* 荷物の価値 */
	int value[] = { 2, 4, 7, 11, 14, 24 };
	
/* 荷物の種類の数 */
	#define AS (sizeof(size)/sizeof(size[0]))
	
/* ナップザックの大きさの上限 */
	#define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
	int i
	  , j
	  , repack_total
	  , total[MAX_M]
	  , choice[MAX_M]
	  , values_sum = 0
	;

	/* 配列をクリアしておく */
	for( i=0; i <= N; i++ ){
		total[i] = 0;
		choice[i] = -1;
	}
	
	/* 荷物 i = 0〜AS までを考慮に入れる */
	for( i=0; i < AS; ++i ){
		for ( j = 0; j <= N; ++j ) {
			if ( j < Nsize[i] )
				continue;

			repack_total = total[ j - Nsize[i] ] + Nvalue[i];
			if ( repack_total > total[j] ) {
				total[j] = repack_total;
				choice[j] = i;
			}
		}

		/* 配列total、choiceの中身を表示する */
		printf( "i = %d\n", i );

		printf( "total = ");
		for( j=0; j <= N; j++ ) {
			printf( "%2d ", total[j] );
		}
		printf( "\n" );

		printf( "choice = " );
		for( j=0; j <= N; j++ ) {
			printf( "%2d ", choice[j] );
		}
		printf( "\n" );
	}
	for ( i = N; choice[i] != -1; i -= Nsize[ choice[i] ] ) {
		printf( "品物 %d (価値%d)を詰め込む\n", choice[i], Nvalue[ choice[i] ] );
	}

	printf( "価値の合計 = %d\n", total[N] );
}

int AskNum( void ) {
	int num;

	printf( "Size of knapsack is " );
	scanf("%d", &num);

	while ( num >= MAX_M ) {
		printf("Not valid number. Please input 0-199.\n");
		printf( "Size of knapsack is " );
		scanf("%d", &num);
	}

	return num;
}

int ExtractNum( int argc, char *argv[] ) {
	int num;

	if ( argc != 2 ) {
		printf("Please input number.\n");
		num = AskNum();
		return num;
	}

	num = atoi(argv[1]);

	if ( num >= MAX_M ) {
		printf("Not valid number. Please input 0-199.\n");
		num = AskNum();
		return num;
	}

	printf( "Size of knapsack is %d\n", num );
	return num;
}

int main(int argc, char *argv[]){
	int m;

	m = ExtractNum( argc, argv );
	
	DynamicProgramming( m, size, value);
	
	return 0;
}