#include "SDL.h"
#include "SDL_image.h"
#include "SDLFn.h"
#include "SDL_ttf.h"
#include "ticTacToe.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

void applySurface(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, clip, dest, &offset);
    return;
}

SDL_Surface *loadImage(char *filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename);

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL )
        {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
        else
        {
            printf("Failed to open image %s\n", filename);
        }
    }

    return optimizedImage;
}

SDL_Surface *init(char *caption)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("Failed to initialize SDL\n");
        return 0;
    }

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if(screen == NULL)
    {
        printf("Failed to set screen video mode\n");
        return 0;
    }

    if(TTF_Init() == -1)
    {
        printf("Error initializg TTF library: %s\n", TTF_GetError());
        return 0;
    }

    SDL_WM_SetCaption(caption, NULL);
    return screen;
}

void cleanup(board *gameBoard)
{
    SDL_FreeSurface(gameBoard->screen);
    SDL_FreeSurface(gameBoard->human);
    SDL_FreeSurface(gameBoard->computer);
    TTF_Quit();
    SDL_Quit();
    return;
}
