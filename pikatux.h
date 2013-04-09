#ifndef PIKATUX_H
#define PIKATUX_H

#include <SDL/SDL.h>
#include <math.h>
typedef struct Pikatux Pikatux;

struct Pikatux
{
    SDL_Rect coord;
    SDL_Surface* sprite[5];
    int step;
};

void initPikatux_sprite(Pikatux *player, SDL_Surface* sprite[5]);
void initPikatux_Pos(Pikatux *player);

void pikatux_step(Pikatux *player);
void pikatux_showSpeed(Pikatux *player, int delay);


#endif //PIKATUX_H
