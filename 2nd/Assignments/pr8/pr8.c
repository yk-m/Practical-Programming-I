#include <stdio.h>
#include <stdlib.h>

#define TRUE      1
#define FALSE     0
#define MAX_SIZE 11

typedef struct character{
	int  no;                        /* キー */
	char name;                      /* 名前 */
	struct character *next_addr;    /* 次のデータのアドレス */
}CELL;

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

CELL *adjacent[MAX_SIZE]; /* 隣接リスト */
int visited[MAX_SIZE];
int path[MAX_SIZE];

/* リスト構造で並んでいる様子を表示する */
void disp(void) {
	int i = 0;
	CELL *current_addr;
	printf("隣接リスト:\n");
	for( i = 0; i < MAX_SIZE; i++ ){
		if( adjacent[i] != NULL ){
			current_addr = adjacent[i];
			do{
				printf("-|%c|-",current_addr->name);
				current_addr = current_addr->next_addr;
			}while( current_addr != NULL );
		}
		printf("\n");
	}
}

/* データの追加 */
void add(int parent, int child) {
	CELL *p;
	CELL *q;
	
	p = (CELL *)malloc(sizeof(CELL));
	p->no = child;
	p->name = 'A' + child;
	p->next_addr = NULL;
	q = adjacent[parent];
	while ( q->next_addr != NULL ) {
		q = q->next_addr;
	}
	q->next_addr = p;
}

/* グラフの初期化 */
void init_graph(void) {
	CELL *p;
	CELL *q;
	int i
	  , j
	;

	for( i = 0; i < MAX_SIZE; i++ ) {
		p = (CELL *)malloc(sizeof(CELL));
		p->no = i;
		p->name = 'A' + i;
		p->next_addr = NULL;
		adjacent[i] = p;
	}

	for( i = 0; i < MAX_SIZE; i++ ) {
		q = adjacent[i];
		for( j = 0; graph_data[i][j] != '\0'; j++ ){
			add( i, graph_data[i][j]-'A' );
		}
	}
	disp();
}

/* 経路の表示 */
void print_path(int num) {
	int i;
	for( i = 0; i <= num; i++ ){
		 printf("%c ", path[i] + 'A' );
	}
	printf("\n");
}

/* 経路の探索（深さ優先探索） */
void search(int num, int now, int end) {
	CELL *p;

	visited[now] = TRUE;
	path[num] = now;

	if ( adjacent[now]->no == end )
		print_path( num );
	else {
		p = adjacent[now];
		num++;
		do {
			if ( !visited[ p->no ] )
				search( num, p->no, end );
			p = p->next_addr;
		} while ( p != NULL );
	}
	visited[now] = FALSE;
}

// void search(int num, int now, int end) {
//  visited[now]にTRUEをセットし訪れたことを記憶
//  path[num]に現在位置をセット
//  現在位置がゴールであれば
//      完成した経路を print_path で表示
//  そうでなければ
//      p=adjacent[now]からリストをたどって
//          visited にセットされていない頂点 i を選んで
//              search を再帰呼び出し（探索手数 num を増やしておく）
//  visited[now]にFALSEをセット
// }

/* メイン関数 */
int main(void) {
	init_graph();
	search( 0, 0, 10 );             /* A(0) から K(10) の経路 */
	return 0;
}