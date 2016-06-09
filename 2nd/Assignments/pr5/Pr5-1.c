/* Pointerを用いたリスト構造の実現 */

/*
 *1 邪魔だったので*2に分離しました
 *3 分離に伴い追加しました
 *4 *1の分離の際，*2でcheck(targetChar)の値を返すことにしたので，それに伴い変更・追加しました
 */

#include <stdio.h>
#include <string.h>

#define MAX_STATION 10
#define ERROR    NULL

typedef struct Station {
	char name[20+1];
	int  time;
	struct Station *next_addr;
} STATION;

int station_num = 0;
STATION station[MAX_STATION];
STATION head;

int get_num(void) {
	int i
	  , d = 0
	  , c = 0
	;
	rewind(stdin);
	for( i = 0; i < 5 && c != '\n' ; i++ ) {
		c = getchar();
		if ( c == '\n' )
			break;
		d = d * 10 + c - '0';
	}
	rewind(stdin);
	return d;
}

int read_data(void) {
	FILE *fp;
	int i;

	fp = fopen("station_data.txt", "r");
	if ( fp == NULL ){
		fprintf(stderr,"CANNOT OPEN station_data.txt\n");
		return -1;
	}
	for( i = 0; i < MAX_STATION; i++, station_num++ ) {
		if ( fscanf(fp,"%s\t%d",station[i].name,&station[i].time) != 2 )
			break;
		station[i].next_addr = &station[i+1];
	}
	fclose(fp);

	head.next_addr = &station[0];
	station[station_num-1].next_addr = NULL;

	return 0;
}

void station_disp(void) {
	STATION *current_addr;
	current_addr = head.next_addr;
	
	while(1){
		printf("|ADDR:%20ld|\n",(long)current_addr);
		printf("|NAME:%20s|\n",current_addr->name);
		printf("|TIME:%20d|\n",current_addr->time);
		printf("|NEXT:%20ld|\n",(long)current_addr->next_addr);
		printf("\n");
		if(current_addr->next_addr == NULL)
			break;
		current_addr = current_addr->next_addr;
	}
}

STATION *check(char target[]) {
	STATION *current_addr;

	current_addr = head.next_addr;
	while(1){
		if( strcmp( target, current_addr->name ) == 0 )
			return current_addr;
		if(current_addr->next_addr == NULL)
			break;
		current_addr = current_addr->next_addr;
	}
	return ERROR;
}

/* 2 */
void getStationName ( const char str[], char stationName[] ) {
	int i;

	printf("%s", str);
	fgets(stationName, 16, stdin);
	for( i=0; stationName[i] != '\n' && i != 15; i++ );
	stationName[i] = '\0';
}

STATION *askStation( const char str[], char targetChar[] ) {
	STATION *current_addr;

	do {
		getStationName( str, targetChar );
		current_addr = check(targetChar);
	} while( current_addr == ERROR );
	return current_addr;
}

void add(void) {
	STATION *current_addr;
	char targetChar[16];
	int a_point;

	/* 3 */
	static const char
	    askStr[]  = "どの駅の後に追加しますか?\nNAME ="
	  , askName[] = "NAME ="
	;

	a_point = station_num++;

	/* 1 */
	getStationName( askName, station[a_point].name );

	printf("TIME =");
	station[a_point].time = get_num();
	station_disp();

	/* 1 */
	current_addr = askStation(askStr, targetChar);

	station[a_point].next_addr = current_addr->next_addr;
	current_addr->next_addr = &station[a_point];

	station_disp();
}

void del(void) {
	int i;
	STATION *forDel
	      , *current_addr
	;
	char targetChar[16];

	/* 3 */
	static const char
	    askStr[] = "どの駅を削除しますか?\nNAME ="
	;
	
	station_disp();

	/* 1 */
	forDel = askStation(askStr, targetChar);

	if ( head.next_addr->next_addr == NULL ) {
		printf("残り１駅しかないため削除できません\n");
		station_disp();
		return;
	}

	/* 4 */
	if( forDel == head.next_addr ){
		head.next_addr = forDel->next_addr;
		station_disp();
		return;
	}

	current_addr = head.next_addr;

	do {
		if ( current_addr->next_addr == forDel ) {
			current_addr->next_addr = forDel->next_addr;
			break;
		}
		current_addr = current_addr->next_addr;
	} while( current_addr != NULL );
	station_disp();
}

int calcTime ( STATION* from_addr, STATION* to_addr ) {
	int sum = 0;
	STATION* current_addr;

	current_addr = from_addr;
	do {
		current_addr = current_addr->next_addr;
		sum += current_addr->time;
	} while ( current_addr != to_addr );
	return sum;
}

void calc(void)
{
	int sum=0, i;
	
	STATION *to_addr
	      , *from_addr    /* 4 */
	      , *current_addr /* 4 */
	;
	char targetFrom[16]
	   , targetTo[16]
	;

	/* 3 */
	static const char
	    askFromStr[] = "FROM(Station Name)="
	  , askToStr[]   = "TO(Station Name)="
	;
	
	printf("どこからどこまでの所要時間を計算しますか？\n");

	/* 1 */
	from_addr = askStation(askFromStr, targetFrom);
	to_addr   = askStation(askToStr  , targetTo);

	printf("%sから",targetFrom);
	printf("%sまでですね\n",targetTo);

	current_addr = head.next_addr;
	while ( current_addr->next_addr != NULL ) {
		if ( current_addr == from_addr ) {
			sum = calcTime( from_addr, to_addr );
			break;
		} else if ( current_addr == to_addr ) {
			sum = calcTime( to_addr, from_addr );
			break;
		}
		current_addr = current_addr->next_addr;
	}

	printf("所要時間は%dです\n",sum);
}

int menu(void)
{
	int c;
	while( 1 ){
		printf("1.表示\n");
		printf("2.追加\n");
		printf("3.削除\n");
		printf("4.所要時間\n");
		printf("5.終了\n");
		c = get_num();
		if( c >= 1 && c <= 5 )
			break;
		else
			printf("1〜5までの数字を入力してください\n");
	}
	switch( c ){
		case 1:
			station_disp();
			break;
		case 2:
			add();
			break;
		case 3:
			del();
			break;
		case 4:
			calc();
			break;
		case 5:
			return 1;
	}
	return 0;
}

int main(void)
{
	int end = 0;
	end = read_data();
	while( !end ){
		end = menu();
	}
	return 0;
}