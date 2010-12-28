#include "ticTacToe.h"
#include "SDL.h"
#include "SDL_image.h"

void applySurface(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect *clip);
SDL_Surface *loadImage(char *filename);
SDL_Surface *init(char *caption);
void cleanup(board *gameBoard);
