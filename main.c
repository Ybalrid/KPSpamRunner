// C standard library
#include <stdio.h>
#include <stdlib.h>

//SDL library
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//projetc files
#include "pikatux.h"
#include "files.h"

int main()
{
    puts("KPSpamRunner");

    //declaring games variables :
    int score = 0;
    const int nbBestScores = 0;
    int distance = 0;
    SDL_Event event; //event catcher
    
    SDL_Rect root;
    root.x = 0;
    root.y = 0;

    Pikatux player; //create the player. he's a Pikatux ! =D
    
    const int windowSizeX=1024;
    const int windowSizeY=768;
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Surface *screen = SDL_SetVideoMode(
            windowSizeX, windowSizeY, 32, SDL_HWSURFACE| SDL_DOUBLEBUF);

    SDL_WM_SetCaption("KPSpamRunner", NULL);
    
    //background
    SDL_FillRect(screen, NULL,SDL_MapRGB(screen->format,  0, 128, 255));
    
    SDL_Surface *background  = IMG_Load("./Background.png");
    SDL_BlitSurface(background, NULL, screen, &root);
    SDL_Flip(screen);
    int run = 1;
    while(run) //render loop
    {
        //GRAPHIC RENDERING
        SDL_Flip(screen);

        //EVENT Processing
        SDL_WaitEvent(&event);
        
        switch (event.type)
        {   
            case SDL_QUIT:
            run = 0;
            break;
        }
    }
    
    SDL_Quit();
    return 0;
}
