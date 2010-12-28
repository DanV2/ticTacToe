#include "ticTacToe.h"

void checkWin(board *gameBoard)
{
	originalPriority(gameBoard);
	int i;
	for(i = 0; i < 8; i++)
	{
		if(gameBoard->block[i] == 3)
		{
			gameBoard->winner = 1;
			return;
		}

		if(gameBoard->win[i] == 3)
		{
			gameBoard->winner = 0;
			return;
		}
	}

	return;
}
