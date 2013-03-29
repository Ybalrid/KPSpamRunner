#include "pikatux.h"


void initPikatux_sprite(Pikatux *player, SDL_Surface* steps[5])
{
    int i;
    
    for(i = 0; i < 5 ; i++)
        player->sprite[i] = steps[i];

    player->step = 2;
}

void initPikatux_Pos(Pikatux *player)
{
    player->coord.x = 0;
    player->coord.y = 0;
}


void pikatux_step(Pikatux *player) //animation of the supertux2 walk cycle 
{
    if (player->sprite == NULL)
    {
        puts("Walk cycle not initialized");
        exit(-1);
    }

    player->step++;

    if (player->step >= 5)
        player->step = 0;
}

