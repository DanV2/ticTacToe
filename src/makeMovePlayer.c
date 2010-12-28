//To-do: Possible improve input method, use fgets instead of getchar
//	 As this may fix current buffer problem's
//	 May also make printing error messages easier
#include "ticTacToe.h"
#include "SDLFn.h"
#include "SDL.h"
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int checkArea(int x, int y, board *gameBoard)
{
    //Check which, if any, square the user clicked in.
    //Return 0-8 for a square or -1 for outside of the squares
    //Also return -1 for a taken square
    int square = -1;
    if(y > 140 && y < 220)
    {
        if(x > 7 && x < 105)
            square = 0;
        else if(x > 115 && x < 270)
            square = 1;
        else if(x > 285 && x < 392)
            square = 2;
        else
            square = -1;
    }
    else if(y > 230 && y < 303)
    {
        if(x > 7 && x < 105)
            square = 3;
        else if(x > 115 && x < 270)
            square = 4;
        else if(x > 285 && x < 392)
            square = 5;
        else
            square = -1;
    }
    else if(y > 355 && y < 477)
    {
        if(x > 7 && x < 105)
            square = 6;
        else if(x > 115 && x < 270)
            square = 7;
        else if(x > 284 && x < 394)
            square = 8;
        else
            square = -1;
    }

    if(gameBoard->squares[square].player != NULL)
        square = -1;

    return square;
}

int makeMovePlayer(board *gameBoard)
{
	int square = -1; //Value of square, init to -1 as this is outside of valid range

	while(square == -1)
	{
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                square = checkArea(event.button.x, event.button.y, gameBoard);
                if(square == -1)
                    break;
                else
                {
                    gameBoard->squares[square].player = gameBoard->human;
                    applySurface(gameBoard->squares[square].x, gameBoard->squares[square].y, gameBoard->human, gameBoard->screen, NULL);
                }
            }
        }
    }

	gameBoard->squares[square].player = gameBoard->human; //Make the move

	return 1;
}
