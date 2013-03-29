#include "pikatux.h"


void initPikatux_sprite(Pikatux *player, SDL_Surface *sprite)
{
    player->sprite = sprite;
}

void initPikatux_Pos(Pikatux *player)
{
    player->coord.x = 0;
    player->coord.y = 0;
}
