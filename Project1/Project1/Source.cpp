#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct gameColor {
	int data;
	struct gameColor * next;
} GameColor;

GameColor * makeNode() 
{
	GameColor * node = (GameColor *)malloc(sizeof(GameColor));
	if (!node)
	{
		return NULL;
	}
	node->data = (rand() % 4) + 1;
	node->next = NULL;
	return node;
}

GameColor * addLast(GameColor * head, GameColor * newNode) {
	GameColor * temp = head;
	if (!head)
	{
		return newNode;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	return head;
}

void freeNode(GameColor * head) {
	GameColor * temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

void print_list(GameColor * head)
{
	GameColor * temp;
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}


int getCount(GameColor * head)
{
	int count = 0; 
	GameColor * current;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}


int findLocation(GameColor * head, int index)
{

	GameColor * current = head;
	int count = 0;
	while (current != NULL)
	{
		if (count == index)
			return(current->data);
		count++;
		current = current->next;
	}
	return NULL;
}

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
	printf("You Loose!");
	freeNode(head);
	return 0;
}
