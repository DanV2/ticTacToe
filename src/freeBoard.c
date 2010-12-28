#include "ticTacToe.h"

void freeBoard(board *gameBoard)
{
	free(gameBoard->squares);
	free(gameBoard->win);
	free(gameBoard->block);
	return;
}
