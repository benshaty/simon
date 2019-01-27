#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct gameColor {
	int data;
	struct gameColor * next;
} GameColor;

int main() {
	int i = 0;
	int state = 1;
	srand(time(NULL));   // Initialization, should only be called once.
	printf("Level 1");
	do
	{
		int r = (rand() % 4) + 1;      // Returns a pseudo-random integer between 0 and RAND_MAX.
		printf("%d , ", r);
	} while (state);
	return 0;
}

GameColor * makeNode() 
{
	GameColor * Node = (GameColor *)malloc(sizeof(GameColor));
	Node->data = (rand() % 4) + 1;
	Node->next = NULL;
}