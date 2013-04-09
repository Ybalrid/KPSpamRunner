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

    SDL_Surface *pressEnter = TTF_RenderUTF8_Blended(font, "Appuyez sur Entrée !",blackFont);

    SDL_Surface* walkCycle[5]; //5 step of annimation
    
    //load it from files
    walkCycle[0] = IMG_Load("./walk-0.png");
    walkCycle[1] = IMG_Load("./walk-1.png");
    walkCycle[2] = IMG_Load("./walk-2.png");
    walkCycle[3] = IMG_Load("./walk-3.png");
    walkCycle[4] = IMG_Load("./walk-4.png");
    
    initPikatux_sprite(&player,walkCycle);
    initPikatux_Pos(&player); 
    char name[128];
    SDL_Surface *dispName = NULL;
    SDL_Surface *dispTime = NULL;
    SDL_Surface *dispScore = NULL;
    char dispScoreString[40];
    char dispTimeString[12]; 
    /////////////////////// GAME RUNNIGN
    int run = 1;
    int stage = TITLE; //will start on the title screen    

    SDL_Rect blitCursor;
    char input[2];
    input[1] = '\0';
    int curTime = SDL_GetTicks();
    int oldTime = curTime;
    int startTime = 0;
    int oldPressTime = 0;    
    int pikatuxRunning = 0;

    while(run) //render loop
    {
        //GRAPHIC RENDERING
        oldTime = curTime;
        curTime = SDL_GetTicks();
        SDL_FillRect(screen, NULL,SDL_MapRGB(screen->format,  0, 128, 255));
        SDL_BlitSurface(background, NULL, screen, &root);
        printf("curTime = %d\n", curTime);
        switch(stage)
        {
            default:
            case TITLE:
                blitCursor.x=768/2 -150;
                blitCursor.y=1024/2 + 20;
                SDL_BlitSurface(pressEnter, NULL, screen, &blitCursor);
                break;
            case SCORE:
                pikatuxRunning = 0;
                printf("SCORE = %d\n", score);
                sprintf(dispScoreString,"SCORE : %d",score);
                dispScore = TTF_RenderUTF8_Blended(font,dispScoreString,blackFont);
                blitCursor.y = 1074/2 + 20;
                blitCursor.x = 768/2 -30;

                SDL_BlitSurface(dispScore,NULL,screen,&blitCursor);
                break;
            case RUN:
                SDL_BlitSurface(player.sprite[player.step], NULL, screen, &player.coord);
                if (pikatuxRunning == 0)
                {
                    startTime = SDL_GetTicks();
                    pikatuxRunning = 1;
                }
                if (curTime - startTime >= 30000)
                {
                    pikatuxRunning = 0;
                    stage = SCORE;
                }

                sprintf(dispTimeString,"Time : %d", 30 - (curTime - startTime)/1000);
                blitCursor.x = root.x + 10;
                blitCursor.y = root.x + 10;
                dispTime =  TTF_RenderUTF8_Blended(font,dispTimeString,blackFont);
                SDL_BlitSurface(dispTime,NULL,screen,&blitCursor);
                
                break;
            case NAME_INPUT:
                dispName = TTF_RenderText_Blended(font, name, blackFont);
                SDL_BlitSurface(dispName, NULL ,screen, &root); 
                break;
        }
    
        //EVENT Processing
        SDL_WaitEvent(&event); //do NOT pause the program
        switch (event.type)
        {   
            case SDL_QUIT:
            run = 0;
            break;

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    run = 0;
                    break;
                case SDLK_RETURN:
                if (stage == TITLE)
                    //stage = NAME_INPUT;
                    stage = RUN;
                break;

                case SDLK_SPACE:
                if(pikatuxRunning)
                {
                    puts("space down");
                    score ++;
                    pikatux_step(&player);
                    pikatux_showSpeed(&player,SDL_GetTicks()-oldPressTime);
                    oldPressTime=SDL_GetTicks();
                }
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
    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}
