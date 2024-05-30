#ifndef LOGIC_H_
#define LOGIC_H_

#include<SDL_mixer.h>

void clickOnCell(game_t *game, int row, int column, Mix_Chunk *click_sound);

int cellsCount(const int *board, int cell);

#endif // LOGIC_H_
