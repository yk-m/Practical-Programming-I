#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int tmp, length=0;
	int previous=0, current;
	char name[128], readline[128];
	FILE *fp;
	
	printf("ファイル名：");
	scanf("%s", name);
	
	fp=fopen(name,"r");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	
	while(fgets(readline, sizeof(readline), fp) != NULL) {
		current = atoi(readline);
		if (current < previous) { printf("Error :-(\n"); exit(1); }
		previous = current;
	}
	printf("Completely!\n");
}
