#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "source.h" // my header file include
#define _CRT_SECURE_NO_WARNINGS // remove the security so we can use scanf


int main() {
	int i = 0;
	int state = 1;
	GameColor * head = NULL;
	GameColor * node;
	char userSelection;
	srand((unsigned int) time(NULL));   // Initialization, should only be called once.
	printf("You need to enter the numbers as shown\n");
	printf("It getting harder each time\n");
	Sleep(2000); // Sleep is a function to make application wait for X ms #include <windows.h>
	system("@cls||clear"); // clear the console
	do
	{
		node = makeNode(); // create new node
		head = addLast(head, node); // add new node to the list
		print_list(head); // print all list items
		Sleep(1500); // Sleep is a function to make application wait for X ms #include <windows.h>
		system("@cls||clear"); // clear the console
		for (i = 0; i < getCount(head); i++)
		{
			userSelection = _getch(); // _getch capture keystroke on keyboard (without need for enter key) #include <conio.h>
			userSelection -= 48; // input is char so the decimal number is -48 from char by ascii table
			if (userSelection == findLocation(head , i))
			{
				printf("corrent!\n");
			}
			else {
				printf("Error!\n");
				state = 0;
				break;
			}
		}
		Sleep(1500); // Sleep is a function to make application wait for X ms #include <windows.h>
		system("@cls||clear"); // clear the console
	} while (state);
	printf("You Loose!\n");
	freeNode(head); // free all list items
	system("PAUSE"); // add "Press any key..." after application end #include <windows.h>
	return 0;
}
