#include <stdio.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        11

int adjacent[MAX_SIZE][MAX_SIZE]; /* 隣接行列 */
int visited[MAX_SIZE];
int open_list[MAX_SIZE]; /* キュー */
	
char *graph_data[] = {
	(char*)"CI",           /* A : C I */
	(char*)"DGH",          /* B : D G H */
	(char*)"ADG",          /* C : A D G */
	(char*)"BCHIJ",        /* D : B C H I J */
	(char*)"FHJ",          /* E : F H J */
	(char*)"EGK",          /* F : E G K */
	(char*)"BCF",          /* G : B C F */
	(char*)"BDEJ",         /* H : B D E J */
	(char*)"AD",           /* I : A D */
	(char*)"DEHK",         /* J : D E H K */
	(char*)"FJ"            /* K : F J */
};

void disp(void) {
	int x, y;
	printf("隣接行列:\n");
	for( y=0; y<MAX_SIZE; y++ ) {
		for ( x=0; x<MAX_SIZE; x++ ) {
			printf("%d ", adjacent[x][y]);
		}
		printf("\n");
	}
}

/* グラフの初期化 */
void init_graph(void)
{
	int x, y;
	for( y=0; y<MAX_SIZE; y++ ) {
		for ( x=0; x<MAX_SIZE; x++ ) {
			adjacent[y][x] = 0;
		}
		for ( x=0; graph_data[y][x] != '\0'; x++ ) {
			adjacent[y][ graph_data[y][x] - 'A' ] = 1;
		}
	}
	disp();
}

/* キューの初期化 */
void init_queue(int *q)
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		q[i] = -1;
	}
}

/* キューの表示 */
void print_queue(int *q)
{
	int i;
	printf("{");
	for( i = 0; i < MAX_SIZE; i++ )
		if( q[i] != -1 )
			printf("%c",q[i]+'A');
	printf("}\n");
}

void print_char( int num ) {
	printf("%c", num+'A');
}

void print_progress( int *q, int num ) {
	printf("searching ... ");
	print_char( num );
	printf("\nopen_list = ");
	print_queue( q );
}

/* キューの中にデータdが存在しているかどうかをチェック */
int check_queue(int *q,int d)
{
	int i;
	for( i = 0; i < MAX_SIZE;i++ )
		if( q[i] == d ) return TRUE;
	return FALSE; 
}

/* キューにデータを入れる */
void enqueue(int *q, int d)
{
	int i = 0;
	while( q[i] != -1 ) i++;
	q[i] = d;
}

/* キューからデータを取り出す */
int dequeue(int *q)
{
	int tmp, i;
	tmp = q[0];
	for ( i=0; q[i] != -1 && i < MAX_SIZE; i++ ) {
		q[i] = q[i+1];
	}
	return tmp;
}

/* 経路の探索（幅優先探索） */
void search(int now, int end)
{
	int num = 0
	  , i
	;
	init_queue( open_list );

	open_list[0] = now;
	visited[now] = TRUE;
	print_progress( open_list, now );

	while ( open_list[0] != -1 ) {

		now = dequeue( open_list );
		visited[now] = TRUE;

		if ( now == end ) {
			printf("Found.\n");
			return;
		}
		for ( i=0; i<MAX_SIZE; i++ ) {
			if ( adjacent[now][i] && !visited[i] && !check_queue( open_list, i ) ) {
				enqueue( open_list, i );
				print_progress( open_list, i );
			} 
		}
	}
}

/* メイン関数 */
int main(void)
{
	init_graph();
	search( 0, 10 );         /* A から K の経路 */
	return 0;
}