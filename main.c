// C standard library
#include <stdio.h>
#include <stdlib.h>

//SDL library
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//projetc files
#include "pikatux.h"
#include "files.h"

//stage gestion
enum
{
    TITLE,
    NAME_INPUT,
    RUN,
    SCORE
};

int main()
{
    puts("KPSpamRunner");

    //declaring games variables :
    int score = 0;
    const int nbBestScores = 0;
    int distance = 0;
    SDL_Event event; //event catcher
    
    SDL_Rect root;//root pixel coord
    root.x = 0;
    root.y = 0;

    Pikatux player; //create the player. he's a Pikatux ! =D
    
    const int windowSizeX=1024;
    const int windowSizeY=768;

    SDL_Init(SDL_INIT_VIDEO); //initialize SDL with video module

    //create a 32bit color window with bouble buffering and put it into the graphic card memory
    SDL_Surface *screen = SDL_SetVideoMode(
            windowSizeX, windowSizeY, 32, SDL_HWSURFACE| SDL_DOUBLEBUF); 
    

    SDL_WM_SetCaption("KPSpamRunner", NULL); //set the window title
    
    //background
    SDL_FillRect(screen, NULL,SDL_MapRGB(screen->format,  0, 128, 255));
    SDL_Surface *background  = IMG_Load("./Background.png");
    SDL_BlitSurface(background, NULL, screen, &root);

    //refresh window 
    SDL_Flip(screen);

    int run = 1;
    int stage = TITLE; //will start on the title screen;
    
    while(run) //render loop
    {
        //GRAPHIC RENDERING
        SDL_Flip(screen);

        switch(stage)
        {
            default:
            case TITLE:
            SDL_FillRect(screen, NULL,SDL_MapRGB(screen->format,  0, 128, 255));
            SDL_BlitSurface(background, NULL, screen, &root);

                break;
        }

        //EVENT Processing
        SDL_PollEvent(&event); //do NOT pause the program
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
