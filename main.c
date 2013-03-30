// C standard library
#include <stdio.h>
#include <stdlib.h>

//SDL library
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

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

typedef SDL_Color TTF_font_color;

int main()
{
    puts("KPSpamRunner");

    SDL_Event event; //event catcher
    
    SDL_Rect root;//root pixel coord
    root.x = 0;
    root.y = 0;

    
    const int windowSizeX=1024;
    const int windowSizeY=768;

    SDL_Init(SDL_INIT_VIDEO); //initialize SDL with video module
    TTF_Init(); //initialize the true type font library
    
    TTF_Font *font = NULL;
    font = TTF_OpenFont("./bolonium.ttf", 70);
    
    TTF_font_color blackFont = {0, 0, 0};
    
    if (font == NULL)
    {
        puts("Font not found");
        return -1;
    }



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



    //GAME object
    
    Pikatux player; //create the player. he's a Pikatux ! =D

    int score = 0;
    const int nbBestScores = 0;
    int distance = 0;

    SDL_Surface *pressEnter = TTF_RenderUTF8_Blended(font, "Appuyez sur Entrée !",blackFont);

    SDL_Surface* walkCycle[5]; //5 step of annimation
    
    //load it from files
    walkCycle[0] = IMG_Load("Walk-0.png");
    walkCycle[1] = IMG_Load("Walk-1.png");
    walkCycle[2] = IMG_Load("Walk-2.png");
    walkCycle[3] = IMG_Load("Walk-3.png");
    walkCycle[4] = IMG_Load("Walk-4.png");
    
    initPikatux_sprite(&player,walkCycle);
    
    char name[128];
    SDL_Surface *dispName = NULL;
    SDL_Surface *dispTime = NULL;

    /////////////////////// GAME RUNNIGN
    int run = 1;
    int stage = TITLE; //will start on the title screen    
    int timeLeft = 30;

    SDL_Rect blitCursor;
    char input[2];
    input[1] = '\0';
    while(run) //render loop
    {
        //GRAPHIC RENDERING
        
        SDL_FillRect(screen, NULL,SDL_MapRGB(screen->format,  0, 128, 255));
        SDL_BlitSurface(background, NULL, screen, &root);

        switch(stage)
        {
            default:
            case TITLE:
                blitCursor.x=768/2 -150;
                blitCursor.y=1024/2 + 20;
                SDL_BlitSurface(pressEnter, NULL, screen, &blitCursor);
                break;
            case SCORE:
                break;
            case RUN:
                break;
            case NAME_INPUT:
                dispName = TTF_RenderText_Blended(font, name, blackFont);
                SDL_BlitSurface(dispName, NULL ,screen, &root); 

                break;
        }

        //EVENT Processing
        SDL_PollEvent(&event); //do NOT pause the program
        switch (event.type)
        {   
            case SDL_QUIT:
            run = 0;
            break;

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_RETURN:
                if (stage == TITLE)
                    //stage = NAME_INPUT;
                    stage = RUN;
                break;
            }



            if (stage == NAME_INPUT) //type text with the keyboard
            {
                if(SDL_KEYDOWN)
                {


                    if (event.key.keysym.sym >= 97 || event.key.keysym.sym <= 122)
                    {
                        if(strlen(input) < 126)
                        {
                            input[0] = (char) event.key.keysym.sym;
                            strcat(name,input);
                        }
                    }

                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                        if(strlen(name) >= 1)
                            name[strlen(name) - 1] = '\0'; 
                }
            }

            break;
        }

        SDL_Flip(screen);
        // SDL_Delay(200);
    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}
