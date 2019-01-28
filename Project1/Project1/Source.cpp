#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "source.h"
#define _CRT_SECURE_NO_WARNINGS


int main() {
	int i = 0;
	int state = 1;
	GameColor * head = NULL;
	GameColor * node;
	char userSelection;
	srand((unsigned int) time(NULL));   // Initialization, should only be called once.
	printf("Level 1\n");
	do
	{
		node = makeNode();
		head = addLast(head, node);
		print_list(head);
		for (i = 0; i < getCount(head); i++)
		{
			userSelection = _getch(); // _getch capture keystroke on keyboard (without need for enter key) #include <conio.h>
			userSelection -= 48;
			if (userSelection == findLocation(head , i))
			{
				printf("corrent!\n");
			}
			else {
				state = 0;
				break;
			}
		}
	} while (state);
	printf("You Loose!\n");
	freeNode(head);
	system("PAUSE");
	return 0;
}
