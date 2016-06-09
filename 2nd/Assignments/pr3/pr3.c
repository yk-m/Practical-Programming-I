#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 256
int next[PATN_LENGTH];
/* テキストとパターンの不一致が見つかったときにどれだけずらすかを示す表 */
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b) /* 二つの数a,bのうち大きい方を返すマクロ */

void printBlank(int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf(" ");
	}
}

void printArrows(int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf(">");
	}
}

void printNext(uchar pattern[], int patn_len) {
	int i;
	for (i = 0; i < patn_len; ++i) {
		printf("%c: next[%2d] =  %d\n", pattern[i], i, next[i]);
	}
}

void printSkip(uchar pattern[], int patn_len) {
	int i;
	for (i = 0; i < patn_len; ++i) {
		printf("%c: skip[%2d] =  %d\n", pattern[i], pattern[i], skip[pattern[i]]);
	}
}

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(uchar text[], uchar pattern[])
{
	int i = 0  /* 注目しているテキストの位置 */
	  , j = 0  /* 注目しているパターンの位置 */
	;
	int text_len
	  , patn_len
	;
	text_len = strlen((char*)text);    /* テキストの長さをセット */
	patn_len = strlen((char*)pattern); /* パターンの長さをセット */
	while ( i < text_len && j < patn_len ) {
		if ( text[i] == pattern[j] ) {
			printf("%c", pattern[j]);
			i++;
			j++;
		} else {
			printf("%c ...failure\n", pattern[j]);
			i = i - j+1;
			j = 0;
			printBlank(i);
		}
	}
	if ( j == patn_len ) {
		printf(" ...success\n");
		return i - patn_len;
	}
	else
		return -1;
}

/* ずらし表を作成する */
void init_next(uchar pattern[])
{
	int patn_len
	  , j
	  , k
	  , m
	;
	patn_len = strlen((char*)pattern); /* パターンの長さをセット */
	for ( j = 0; j < patn_len; j++ ) {
		if ( j < 1 )
			next[j] = 1;
		else {
			for ( k = 1; k < j; k++ ) {
				for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ );
				if ( m == j )
					break;
			}
			next[j] = k;
		}
	}
}

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(uchar text[], uchar pattern[])
{
	int i = 0  /* 注目しているテキストの位置 */
	  , j = 0  /* 注目しているパターンの位置 */
	;
	int text_len
	  , patn_len
	;
	text_len = strlen((char*)text);    /* テキストの長さをセット */
	patn_len = strlen((char*)pattern); /* パターンの長さをセット */
	/* テキストの最後尾に行き当たるか、パターンが見つかるまで繰り返す */
	while ( i < text_len && j < patn_len ) {
		if ( text[i] == pattern[j] ) {
			printf("%c", pattern[j]);
			i++;
			j++;
		} else {
			printf("%c ...failure\n", pattern[j]);
			j -= next[j];
			if ( j < 0 ) {
				i++;
				j++;
			}
			printBlank(i);
		}
	}
	if ( j == patn_len ) {
		printf(" ...success\n");
		return i - patn_len;
	}
	else
		return -1;
}

/* BM法用のずらし表を作成する */
void init_skip(uchar pattern[])
{
	int i
	  , patn_len = strlen((char*)pattern)
	;
	for( i = 0; i < 256; i++ )
		skip[i] = patn_len;
	for( i = 0; i < patn_len; i++ )
		skip[pattern[i]] = patn_len - i - 1;
}


/* 文字列textから文字列patternを検索する(BM法) */
int bm_search(uchar text[], uchar pattern[]) {
	int i; /* 注目しているテキストの位置 */
	int j; /* 注目しているパターンの位置 */
	int text_len, patn_len;

	text_len = strlen((char*)text);    /* テキストの長さをセット */
	patn_len = strlen((char*)pattern); /* パターンの長さをセット */

	i = patn_len - 1;

	while( i < text_len ) {
		j = patn_len - 1;
		printArrows(i);
		printf("%c", pattern[j]);
		while( text[i] == pattern[j] ) {
			if ( j == 0 ) {
				printf("  ...success\n");
				return i;
			}
			i--;
			j--;
			printf("\n");
			printBlank(i);
			printf("%c", pattern[j]);
		}
		printf("  ...failure\n");
		i += skip[ text[i] ] > patn_len-j ? skip[ text[i] ] : patn_len-j;
	}
	return -1;
}

void callTextSearch(uchar text[], uchar pattern[]) {
	int position
	  , patn_len
	;

	patn_len = strlen((char*)pattern); /* パターンの長さをセット */

#if BF
	printf("--- B F ---\n");
	printf("%s\n",text);
	position = brute_force_search(text, pattern);
	printf("position=%d\n",position);
#endif

#if KMP
	printf("--- KMP ---\n");
	init_next(pattern);
	printNext(pattern, patn_len);
	printf("%s\n",text);
	position = kmp_search(text, pattern);
	printf("position=%d\n",position);
#endif


#if BM
	printf("--- B M ---\n");
	init_skip(pattern);
	printSkip(pattern, patn_len);
	printf("%s\n",text);
	position = bm_search(text, pattern);
	printf("position=%d\n",position);
#endif

}

int main(void)
{
	uchar text[TEXT_LENGTH+1];
	uchar pattern[PATN_LENGTH+1];

	strcpy((char*)text,"aabbabcabc");
	strcpy((char*)pattern,"abcab");
	callTextSearch(text, pattern);

	strcpy((char*)text,"oizumikizuninmizui");
	strcpy((char*)pattern,"ninininm");
	callTextSearch(text, pattern);

	return 0;
}