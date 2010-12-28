#ifndef _TicTacToe_H
#define _TicTacToe_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"

SDL_Event event;

//square struct, member variable of board
//Also, any changes to the struct will likely require changes to initializeBoard()
typedef struct
{
	SDL_Surface *player; //Will contain 'X', 'O', or ' ' depending on which player has the square
	int priority; //Calculated and used to determine which square the computer should take
    int x, y;
} square;

typedef struct
{
    SDL_Surface *screen, *human, *computer; //Images for screen, x, and o
	square *squares; //Pointer to squares, actual gameboard
	int turn; //0 = computer, 1 = player
	int *win; //Used to keep track of the number of squares that are the same in each row
	int *block; //Flag used to indicate if a move will be a block
	int winner; //0 = computer wins; 1 = player wins
} board;

board*	initializeBoard		( ); //Create board and allocate memory
void	freeBoard		    ( board *gameBoard ); //Destroy board and deallocate memory
void	drawBoard		    ( board *gameBoard ); //Draw gameboard, used each turn
void	originalPriority    ( board *gameBoard ); //Used by AI to calculate the priority of each square
void	checkWin		    ( board *gameBoard ); //Used to check if someone has won at the end of a turn
void	makeMoveComp		( board *gameBoard ); //Contains code to control AI
int 	makeMovePlayer		( board *gameBoard ); //Prompts player for move
void	printError		    ( int error );	      //Prints error message based on int passed to it

#endif /* _TicTacToe_H */
