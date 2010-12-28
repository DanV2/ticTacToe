//To-do: Nothing for now.  If changes are made to the struct, changes may be needed here as well.
#include "ticTacToe.h"
#include "SDLFn.h"
#include "SDL.h"

//Simple, allocates for necessary pointers and checks to make sure they were all created properly
//Also initializes chars
board* initializeBoard( )
{
	board *gameBoard;

	gameBoard = malloc(sizeof(board));
	if(gameBoard == NULL)
	{
		printError(0);
		return NULL;
	}

	gameBoard->screen = init("Tic Tac Toe");
	//SDL_Surface *background = loadImage("board.png");
	//applySurface(0, 0, loadImage("img/board.png"), gameBoard->screen, NULL);


	gameBoard->squares = malloc(sizeof(square) * 9);
	if(gameBoard->squares == NULL)
	{
		printError(0);
		return NULL;
	}

	gameBoard->win = malloc(sizeof(int) * 8);
	if(gameBoard->win == NULL)
	{
		printError(0);
		return NULL;
	}

	gameBoard->block = malloc(sizeof(int) * 8);
	if(gameBoard->block == NULL)
	{
		printError(0);
		return NULL;
	}

	int i;
	for(i = 0; i < 9; i++)
	{
		gameBoard->squares[i].player = NULL;
		gameBoard->squares[i].priority = 0;
        switch(i)
        {
            case 0:
                gameBoard->squares[i].x = 20;
                gameBoard->squares[i].y = 140;
                break;

            case 1:
                gameBoard->squares[i].x = 155;
                gameBoard->squares[i].y = 140;
                break;

            case 2:
                gameBoard->squares[i].x = 320;
                gameBoard->squares[i].y = 140;
                break;

            case 3:
                gameBoard->squares[i].x = 20;
                gameBoard->squares[i].y = 250;
                break;

            case 4:
                gameBoard->squares[i].x = 155;
                gameBoard->squares[i].y = 250;
                break;

            case 5:
                gameBoard->squares[i].x = 320;
                gameBoard->squares[i].y = 250;
                break;

            case 6:
                gameBoard->squares[i].x = 20;
                gameBoard->squares[i].y = 370;
                break;

            case 7:
                gameBoard->squares[i].x = 155;
                gameBoard->squares[i].y = 370;
                break;

            case 8:
                gameBoard->squares[i].x = 320;
                gameBoard->squares[i].y = 370;
                break;
        }
	}

	gameBoard->human = NULL;
	gameBoard->computer = NULL;
	gameBoard->winner = -1;
	return gameBoard;
}
