/*
 * makeMoveComp.c
 *
 * This function does not have the bulk of the AI code in it.
 * Instead, it calls the function that does (calculatePriority())
 * and then uses the information returned by it to make a move.
 * The actual move made is randomized among all of the squares
 * that have the max priority value.
 *
 * TO-DO:
 * Add alternate AI's to choose from, at user's discretion or
 * randomly.  One AI should be used for the whole game.
 * Switching AI mid move would be something to try, but it
 * might not work so well.
 *
 * But for now, nothing...
 */

#include "ticTacToe.h"
#include "SDLFn.h"

void makeMoveComp( board *gameBoard )
{

	//Call the function that sets the priority value for each element
	//of the gameBoard array
	originalPriority(gameBoard);

	//Declare loop variables i & j
	//square is the index of the square that will be changed
	//max is the highest priority, used to randomize the actual
	//move when many squares have the max priority
	int i, j = 0, max = 0, square;
	//maxSquares is used to keep track of the squares that have
	//the highest priority for randomization
	int *maxSquares = malloc(sizeof(int) * 9);

	//Cycle through and find highest priority
	for(i = 0; i < 9; i++)
		if(gameBoard->squares[i].priority > max)
			max = gameBoard->squares[i].priority;

//	printf("Max is: %i\n", max);

	//Track all squares that have the max priority
	for(i = 0; i < 9; i++)
	{
		if(gameBoard->squares[i].priority == max)
		{
			maxSquares[j] = i;
			j++;
//			printf("Square %i has priority %i\n", i, gameBoard->squares[i].priority);
		}
	}

	//And randomly choose one
	srand(time(NULL));
	square = maxSquares[rand() % j];

//	printf("j = %i\nComp will make move at square %i\n", j, square);

//	getchar();

	//And actually make the move :D
	gameBoard->squares[square].player = gameBoard->computer;
    applySurface(gameBoard->squares[square].x, gameBoard->squares[square].y, gameBoard->computer, gameBoard->screen, NULL);

	return;
}
