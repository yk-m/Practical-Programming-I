
#include <stdio.h>
#define BUF_SIZE 32

int checksp(int c)
{
	if ( c == ' ' || c == '\t' || c == '\n') return 1;
	return 0;
}
int strcheck(int c)
{
	if ( c == ' ' ) return 2;
	if ( c == '\t' || c == '\n') return 1;
	return 0;
}

void updateChar(char *s, int pos) {
	*s = *(s+pos);
}

int searchNext(char *s, int pos) {
	while( checksp( *(s+pos) ) ){
		pos++;
	}
	return pos;
}

void compress(char *s)
{
	int pos = 1
	  , type
	;

	pos = searchNext(s, pos);
	updateChar(s++, pos);

	while( *(s+pos) != '\0' ){
		type = strcheck( *(s+pos) );
		switch (type) {
			case 0 :
				updateChar(s++, pos);
				break;
			case 1 :
				pos = searchNext(s, pos);
				updateChar(s++, pos);
				break;
			case 2 :
				if ( *(s+pos+1) == ' ' || *(s+pos+1) == ',' || *(s+pos+1) == '.' || *(s+pos+1) == '\0' ) {
                    pos++;
				} else {
					updateChar(s++, pos);
                }
				break;
		}
	}
	*s = '\0';
}


int main(void)
{
	char s[] = "    Hello   ,  Jim ! How \t are \n\t\t you?    ";
	printf("Before = \"%s\"\n",s);
	compress(s);
	printf("After  = \"%s\"\n",s);
	return 0;
}
