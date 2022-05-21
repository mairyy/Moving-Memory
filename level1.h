#ifndef LEVEL1_H
#define LEVEL1_H

#include "common.h"
#include "pictures.h"
#include <SDL_mixer.h>

static SDL_Texture* pic0Texture1 = NULL, *pic1Texture1 = NULL, *pic2Texture1 = NULL, *pic3Texture1 = NULL;
static SDL_Texture* scoreTexture1 = NULL;

void loadPictures1(Picture *pics, SDL_Renderer* gRenderer, SDL_Surface* gScreen);
void loadLevel1(int &level, Picture *pics, int &totalPics, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer);
void playLevel1(SDL_Surface* gScreen,  SDL_Texture* gTexture, TTF_Font* gFont, int &score, SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin);
void clean1();

#endif