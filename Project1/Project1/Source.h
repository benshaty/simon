#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS

// define the GameColor struct
typedef struct gameColor {
	int data;
	struct gameColor * next;
} GameColor;

// create new node
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

// add new node to the last location in the list
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

// free all list items
void freeNode(GameColor * head) {
	GameColor * temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

// print all list data
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

// count all list items
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

// find list item by location
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