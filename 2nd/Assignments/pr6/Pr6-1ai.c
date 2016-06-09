/* ハッシュ法によるデータ管理（チェイン法版） */

#include <stdio.h>
#include <stdlib.h>

#define ERROR    -1
#define HASH_SIZE  9
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

/* ハッシュ表からリスト構造で並んでいる様子を表示する */
void disp(void)
{
		int i = 0;
		struct character *q;

		for( i = 0; i < HASH_SIZE; i++ ) {
				printf("-|%d|",i);
				printf("%2ld|-",(long)HashTable[i]);
				if( HashTable[i] != NULL) {
					q = HashTable[i];
					do {

						printf("-|%d|" , i);
						printf("%ld:"  , (long)q);
						printf("%2d:"  , q->no);
						printf("%s:"   , q->name);
						printf("%ld|-" , (long)q->next_addr);
						// printf("-|%d|%2ld:%d:%s:%ld|-",i,(long)q,q->no,q->name,(long)q->next_addr);
						q = q->next_addr;
					} while (q != NULL);
						//↑リスト構造で連結しているデータを表示
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

		p = (CHARACTER *)malloc(sizeof(CHARACTER *));//追加データのためのメモリを確保
		
		printf("NO＝");
		p->no = get_num();
		printf("名前＝");
		fgets(p->name,16,stdin);
		for( j=0; p->name[j] != '\n' && j != 15; j++ );
		p->name[j] = '\0';
		/* ↑改行コードを削除するための処理 */
		p->next_addr = NULL;   
		h = hash( p->no );
		if( HashTable[h] == NULL ) {
				HashTable[h] = p;
				//↑HashTable[h]にまだデータが存在してなかったときの処理
		} else {
			q = HashTable[h];
				do{
					if(q->next_addr == NULL){
						q->next_addr = p;
						break;
					}
					q = q->next_addr;
				}while(q != NULL);
				//↑HashTable[h]に既にデータが存在していたときの処理 
		}
		p =  p->next_addr;

		disp();
}

/* データの削除 */
int del(void)
{
		int i, h;
		struct character *q,*head,*target;
		int point;

		disp();
		printf("NO＝");
		point = get_num();
		h = hash(point);
		if(HashTable[h] != NULL){
			q = HashTable[h];
		
			if( point == q->no){
				HashTable[h] = q->next_addr;
				disp();
				return 0;
			//↑キーが見つかったら該当データを削除してdisp()を呼ぶ
			}else{
				target = q->next_addr;
				while(target != NULL){
					if(target->no == point){
						q->next_addr = target->next_addr;
						disp();
						return 0; 
					}
					target = q;
					q = q->next_addr;

				}
			}
		}
		printf("NOT FOUND\n");
		return ERROR;//↑キーが見つからなかったら"NOT FOUND."を表示してERRORを返す
}

/* データの探索 */
int search(void)
{
		int i, h;
		struct character *q,*head,*target;
		int point;
		printf("NO＝");
		point = get_num();
		h = hash(point);
		target = HashTable[h];
			while(target != NULL){
				if(target->no == point){
					printf("探索キー%dに対応するデータは%sです。\n",point,target->name);						
					disp();
					return 0; 
				}
				target = target->next_addr;
			}
		printf("NOT FOUND\n");
		return ERROR;//↑キーが見つからなかったら"NOT FOUND."を表示してERRORを返す					
}


/* メニュー */
int menu(void)
{
		int c;
		while( 1 ) {
				printf("1.表示\n");      // 課題5と同様の理由で，"表"と"示"の間に"\"を挿入
				printf("2.追加\n");
				printf("3.削除\n");
				printf("4.探索\n");
				printf("5.終了\n");
				c = get_num();
				if( c >= 1 && c <= 5 )  break;
				else printf("1〜5までの数字を入力してください\n");
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