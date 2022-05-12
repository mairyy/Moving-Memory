#ifndef LEVEL1_H
#define LEVEL1_H

#include "common.h"
#include "pictures.h"
#include <SDL_mixer.h>

void loadLevel1(Picture *pics, int &totalPics, SDL_Texture* pic0Texture, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer);
void playLevel1(SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin, SDL_Texture* pic0Texture, SDL_Texture* pic1Texture, SDL_Texture* pic2Texture, SDL_Texture* pic3Texture);

#endif