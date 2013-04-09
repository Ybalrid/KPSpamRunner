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
    player->coord.x = 80;
    player->coord.y = (800/2) + 110 ;
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


void pikatux_showSpeed(Pikatux *player, int delay)
{
    printf("delay = %d", delay);
    if (delay < 70)
        player->coord.x = 740;
    else
        player->coord.x = 740-delay;
    if(player->coord.x < 80)
        player->coord.x = 80;
}
