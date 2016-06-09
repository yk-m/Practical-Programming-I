#include <stdio.h>

#define LISTLENGTH	10

void printList(int *l, int length)
{
	int i;
	for (i = 0; i < length; ++i)
	{
		printf("%d / ", l[i]);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int list[LISTLENGTH];
	int i;

	for (i = 0; i < LISTLENGTH; ++i)
	{
		list[i] = i;
	}

	printList(list, LISTLENGTH);

	list = &list[1];

	printList(list, LISTLENGTH-1);

	return 0;
}