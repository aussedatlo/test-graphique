#include <SDL/SDL.h>
#include <stdio.h>

#define SCREEN_X 800
#define SCREEN_Y 480
#define MARKER_SIZE 13
#define COLOR 0x0
#define BACKGROUND 0xFFFFFFFF

int print_marker(SDL_Surface *ecran, int x, int y) {
    int i, j, pos;

    SDL_LockSurface(ecran);

    for (i=-MARKER_SIZE; i<=MARKER_SIZE; i++) {
        for (j=-MARKER_SIZE; j<=MARKER_SIZE; j++) {
            pos = SCREEN_X*(y+i)+ (x+j);
            if (pos > 0 && pos < SCREEN_X*SCREEN_Y)
                if ((i*i + j*j) <= MARKER_SIZE*MARKER_SIZE)
                *((unsigned int *)ecran->pixels + SCREEN_X*(y+i)+ x+j) = COLOR;
        }
    }
    SDL_UnlockSurface(ecran);
    SDL_Flip(ecran);
}

int waitEvent (SDL_Event *event)
{
    while ( 1 ) {
        SDL_PumpEvents();
        switch(SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_ALLEVENTS)) {
            case -1: return 0;
            case 1: return 1;
            case 0: SDL_Delay(3);
        }
    }
}

void WipeSurface(SDL_Surface *surface)
{
    int i;

    SDL_LockSurface(surface);
    for (i=0; i<SCREEN_X * SCREEN_Y; i++)
        *((unsigned int *)surface->pixels + i) = BACKGROUND;
    SDL_UnlockSurface(surface);
    SDL_Flip(surface);
}

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Event e;
    Uint32 clearColor;
    int x, y;

    /* Initialize the SDL library (starts the event loop) */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr,
            "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Clean up on exit, exit on window close and interrupt */
    atexit(SDL_Quit);

    ecran = SDL_SetVideoMode(SCREEN_X, SCREEN_Y, 0, SDL_HWSURFACE);

    WipeSurface(ecran);

    /* Loop until quit */
    while (waitEvent(&e) >= 0) {
        switch (e.type) {
            case SDL_MOUSEMOTION: {
                SDL_GetMouseState(&x, &y);
                print_marker(ecran, x, y);
                printf("x:%d, y:%d\n", x, y);
            }
            break;
            case SDL_QUIT: {
                printf("Quit requested, quitting.\n");
                exit(0);
            }
            break;
        }
    }
}