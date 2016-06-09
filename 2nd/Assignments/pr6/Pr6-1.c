/* ハッシュ法によるデータ管理（チェイン法版） */

#include <stdio.h>
#include <stdlib.h>

#define ERROR		-1
#define HASH_SIZE	9
typedef struct character {
	int no;                         /* キー */
	char name[16];                  /* 名前 */
	struct character *next_addr;    /* 次のデータのアドレス */
} CHARACTER;
CHARACTER *HashTable[HASH_SIZE];

/* 数値の入力用関数 */
int get_num(void)
{
	int  i;
	int  d = 0;
	int  c = 0;
	rewind(stdin);
	for( i = 0; i < 5 && c != '\n' ; i++ ) {
		/* 5ケタまで */
		c = getchar();
		if ( c == '\n' ) break;
		d = d * 10 + c - '0';
	}
	rewind(stdin);
	return d;
}

void dispChar( int hash, CHARACTER *target ) {
	printf("-|%d|" , hash);
	printf("%ld:"  , (long)target);
	printf("%2d:"  , target->no);
	printf("%s:"   , target->name);
	printf("%ld|-" , (long)target->next_addr);
}
void dispList( int hash, CHARACTER *target ) {
	struct character *current_addr;
	current_addr = target;
	do {
		dispChar(hash, current_addr);
		current_addr = current_addr->next_addr;
	} while ( current_addr != NULL );
}
/* ハッシュ表からリスト構造で並んでいる様子を表示する */
void disp(void)
{
	int i = 0;
	struct character *current_addr;
	for( i = 0; i < HASH_SIZE; i++ ) {
		printf("-|%d|",i);
		printf("%2ld|-",(long)HashTable[i]);
		if( HashTable[i] != NULL ) {
			dispList( i, HashTable[i] );
		}
		printf("\n");
	}
}

/* ハッシュ値の計算 */
int hash(int h)
{
	return h % HASH_SIZE;
}

/* データの追加 */
void add(void)
{
	struct character *p;
	struct character *q;
	int i, j;
	int h;

	p = (CHARACTER *)malloc(sizeof(CHARACTER));

	printf("NO＝");
	p->no = get_num();
	printf("名前＝");
	fgets(p->name,16,stdin);
	for( j=0; p->name[j] != '\n' && j != 15; j++ );
	p->name[j] = '\0';

	p->next_addr = NULL;
	h = hash( p->no );
	if( HashTable[h] == NULL ) {
		HashTable[h] = p;
	} else {
		q = HashTable[h];
		while ( q->next_addr != NULL)
			 q = q->next_addr;
		q->next_addr = p;
	}
	disp();
}

/* データの削除 */
int del(void)
{
	int i, h;
	struct character *current_addr,*head,*target;
	int point;
	disp();
	printf("NO＝");
	point = get_num();
	h = hash(point);
	if ( HashTable[h] != NULL ) {
		head = HashTable[h];
		if ( head->no == point ) {
			HashTable[h] = head->next_addr;

			disp();
			return 0;
		} else {
			current_addr = head;
			target = head->next_addr;
			while ( target != NULL ) {
				if ( target->no == point ) {
					current_addr->next_addr = target->next_addr;
					disp();
					return 0;
				}
				target = current_addr;
				current_addr = current_addr->next_addr;
			}
		}
	}

	printf("NOT FOUND.\n");
	return ERROR;
}

/* データの探索 */
int search(void)
{
	int i, h;
	struct character *current_addr,*head,*target;
	int point;
	printf("NO＝");
	point = get_num();
	h = hash(point);
	head = HashTable[h];

	if ( HashTable[h] != NULL ) {
		if ( head->no == point ) {
			printf("探索キー%dに対応するデータは%sです．\n", point, head->name);
			dispChar( h, head );
			printf("********************************************\n\n");
			disp();

			return 0;
		} else {
			current_addr = head->next_addr;
			while ( current_addr != NULL ) {
				if ( current_addr->no == point ) {
					printf("探索キー%dに対応するデータは%sです．\n", point, head->name);
					dispChar( h, head );
					printf("\n********************************************\n\n");
					disp();
					
					return 0;
				}
			}
		}
	}

	printf("NOT FOUND.\n");
	return ERROR;
}


/* メニュー */
int menu(void)
{
	int c;
	while( 1 ) {
		printf("1.表\示\n");      // 課題5と同様の理由で，"表"と"示"の間に"\"を挿入
		printf("2.追加\n");
		printf("3.削除\n");
		printf("4.探索\n");
		printf("5.終了\n");
		c = get_num();
		if( c >= 1 && c <= 5 )
			break;
		else
			printf("1〜5までの数字を入力してください\n");
	}
	switch( c ) {
		case 1:
			disp();
			break;
		case 2:
			add();
			break;
		case 3:
			del();
			break;
		case 4:
			search();
			break;
		case 5:
			return 1;
	}
	return 0;
}

int main(void)
{
	int i, end = 0;
	/* ハッシュ表を初期化 */
	for( i = 0; i < HASH_SIZE; i++ )
		HashTable[i] = NULL;
	while( !end ) {
		end = menu();
	}
	return 0;
}
