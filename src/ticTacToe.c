/*
    To Do:
    Add cleanup before returning
    Add error checking
    Finish game!

    NEXT: edit makeMovePlayer, abstract coordinate info to its own function
          Maybe add member variables to the square object, x and y, to keep track of coords
*/
#include "ticTacToe.h"
#include <unistd.h>
#include <string.h>
#include "SDLFn.h"
#include "SDL.h"
#include "SDL_ttf.h"

int main(int argc, char **argv)
{
    board *gameBoard = initializeBoard();
    SDL_Surface *title = loadImage("img/pick.png");
    TTF_Font *font = TTF_OpenFont("lazy.ttf", 32);

    applySurface(0, 0, title, gameBoard->screen, NULL);

    while(SDL_Flip(gameBoard->screen) != -1 && gameBoard->human == NULL)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int x, y;
                x = event.button.x;
                y = event.button.y;

                if((x >= 45 && x <= 190) && (y >= 145 && y <= 260))
                {
                    gameBoard->human = loadImage("img/x.png");
                    gameBoard->computer = loadImage("img/o.png");
                }
                if((x >= 425 && x <= 520) && (y >= 150 && y <= 250))
                {
                    gameBoard->human = loadImage("img/o.png");;
                    gameBoard->computer = loadImage("img/x.png");;
                }
            }
        }
    }
    Uint32 whiteKey = SDL_MapRGB(gameBoard->human->format, 0xFF, 0xFF, 0xFF);
    SDL_SetColorKey(gameBoard->human, SDL_SRCCOLORKEY, whiteKey);

    whiteKey = SDL_MapRGB(gameBoard->computer->format, 0xFF, 0xFF, 0xFF);
    SDL_SetColorKey(gameBoard->computer, SDL_SRCCOLORKEY, whiteKey);

    SDL_FillRect(gameBoard->screen, NULL, 0xFFFFFFFF);
    SDL_Flip(gameBoard->screen);
    SDL_Surface *message;
    SDL_Color textColor = {0,0,0};
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    srand(time(NULL));
    switch(rand() % 2)
    {
        case 0:
            message = TTF_RenderText_Solid(font, "Computer gets the first move", textColor);
            applySurface(0, 0, message, gameBoard->screen, NULL);
            gameBoard->turn = 0;
            break;

        case 1:
            message = TTF_RenderText_Solid(font, "Player gets the first move", textColor);
            applySurface(0, 0, message, gameBoard->screen, NULL);
            gameBoard->turn = 1;
            break;
    }

    SDL_Flip(gameBoard->screen);

    int enter = 0;
    while(!enter)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                enter = 1;
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                enter = 1;
        }
    }
    applySurface(0, 0, loadImage("img/board.png"), gameBoard->screen, NULL);
    int turn = 0;
    while(SDL_Flip(gameBoard->screen) != -1)
    {
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                return 0;
        if(gameBoard->turn == 0)
        {
            makeMoveComp(gameBoard);
            gameBoard->turn = 1;
            turn++;
            if(turn == 9)
                break;
            checkWin(gameBoard);
            if(gameBoard->winner != -1)
                break;
        }
        else if(gameBoard->turn == 1)
        {
            if(makeMovePlayer(gameBoard) == 0)
                return 0;
            gameBoard->turn = 0;
            turn++;
            if(turn == 9)
                break;
            checkWin(gameBoard);
            if(gameBoard->winner != -1)
                break;
        }
    }

    SDL_FreeSurface(message);

    if(gameBoard->winner == 0)
        message = TTF_RenderText_Solid(font, "Computer wins!", textColor);
    else if(gameBoard->winner == 1)
        message = TTF_RenderText_Solid(font, "You win!", textColor);
    else
        message = TTF_RenderText_Solid(font, "Tie...", textColor);

    applySurface(0, 0, message, gameBoard->screen, NULL);

    enter = 0;
    while(SDL_Flip(gameBoard->screen) != -1 && !enter)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                enter = 1;
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                enter = 1;
        }
    }
    cleanup(gameBoard);

    return 0;
}
    /*
	if (system("cls"))
		system("clear");

	printf("TicTacToe v1.0\nBy Daniel Bauer\n\n");

	printf("Number of games to play: ");
	int games, i;
	char buffer[BUFFER_SIZE];

	fgets(buffer, strlen(buffer), stdin);
	if(sscanf(buffer, "%d", &games) == 0)
	{
		printf("Input error, expected integer\n");
		return 0;
	}

	for(i = 0; i < games; i++)
	{
		if (system("cls"))
			system("clear");
		board *gameBoard = initializeBoard( );
		SDL_Flip(gameBoard->screen);
		while(gameBoard->human != 'X' && gameBoard->human != 'O')
		{
			printf("Pick X or O: ");
//			fgets(buffer, strlen(buffer), stdin);
//			sscanf(buffer, "%c", &gameBoard->human);
            scanf("%c", &gameBoard->human);
			gameBoard->human = toupper(gameBoard->human);
		}
		if(gameBoard->human == 'X')
			gameBoard->computer = 'O';
		else
			gameBoard->computer = 'X';

		srand(time(NULL));
		int i;
//		while(getchar()) {}

		switch(rand() % 2)
		{
			case 0:
				printf("Computer gets first move.\n\n");
                if(system("PAUSE"))
                    system("sleep 5");
				makeMoveComp(gameBoard);

				for(i = 0; i < 4; i++)
				{
					makeMovePlayer(gameBoard);
					checkWin(gameBoard);
					if(gameBoard->winner != -1)
						break;
					makeMoveComp(gameBoard);
					checkWin(gameBoard);
					if(gameBoard->winner != -1)
						break;
				}
				break;

			case 1:
				printf("Player gets first move.\n\n");
                if(system("PAUSE"))
                    system("sleep 5");
				drawBoard(gameBoard);
				makeMovePlayer(gameBoard);

				for(i = 0; i < 4; i++)
				{
					makeMoveComp(gameBoard);
					checkWin(gameBoard);
					if(gameBoard->winner != -1)
						break;
					makeMovePlayer(gameBoard);
					checkWin(gameBoard);
					if(gameBoard->winner != -1)
						break;
				}
				break;
		}

		switch(gameBoard->winner)
		{
			case -1:
				printf("Looks like a tie this time!\n");
				break;

			case 0:
				printf("I win!  Better luck next time!\n");
				break;

			case 1:
				printf("You win!  Congratulations!\n");
				break;
		}
		if(system("PAUSE"))
            system("sleep 5");

		freeBoard(gameBoard);
	}
		return 0;
}
*/
