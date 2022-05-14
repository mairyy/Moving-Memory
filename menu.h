#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "pictures.h"
#include "SDL_mixer.h"

void mainLayer(SDL_Renderer* gRenderer, SDL_Surface* gScreen, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void helpLayer(SDL_Renderer* gRenderer, SDL_Surface* gScreen, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void winLayer(Picture* pics, SDL_Surface* gScreen, SDL_Renderer* gRenderer, Mix_Chunk* gWin, int &level, int &totalPics);
void nextLevelLayer(SDL_Surface* gScreen, SDL_Renderer* gRenderer);

#endif