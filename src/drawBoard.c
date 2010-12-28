//It works, so why change it?
#include "ticTacToe.h"

void drawBoard( board *gameBoard )
{
	int i;
	if (system("cls"))
		system("clear");

	printf("     |     |                 |     |\n");
	for(i = 0; i < 8; i += 3)
	{
//		printf("  %c  |  %c  |  %c           %i  |  %i  |  %i\n", gameBoard->squares[i].player, gameBoard->squares[i + 1].player, gameBoard->squares[i + 2].player, i + 1, i + 2, i + 3);

//The next line would print out priorities as well in a new board next to the regular one
//Useful for debugging, but I think you would need to remove the newline from the end of the previous
//printf and set a tab or two at the beginning of the debug printf

//		printf("  %c  |  %c  |  %c           %i  |  %i  |  %i\n", gameBoard->squares[i].player, gameBoard->squares[i + 1].player, gameBoard->squares[i + 2].player, gameBoard->squares[i].priority, gameBoard->squares[i + 1].priority, gameBoard->squares[i + 2].priority);

//		printf("     |     |                 |     |\n");
		if(i != 6)
		{
//			printf("-----+-----+-----       -----+-----+-----\n");
//			printf("     |     |                 |     |\n");
		}
	}

	return;
}

