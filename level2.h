#ifndef LEVEL2_H
#define LEVEL2_H

#include "common.h"
#include "pictures.h"
#include <SDL_mixer.h>

static SDL_Texture* pic0Texture2 = NULL, *pic1Texture2 = NULL, *pic2Texture2 = NULL, *pic3Texture2 = NULL, *pic4Texture2 = NULL, *xTexture2 = NULL;
static SDL_Texture* scoreTexture2 = NULL;

void loadPictures2(Picture *pics, SDL_Renderer* gRenderer, SDL_Surface* gScreen);
void loadLevel2(int &level, Picture *pics, int &totalPics, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer);
void playLevel2(SDL_Surface* gScreen,  SDL_Texture* gTexture, TTF_Font* gFont, int &score, SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin);
void clean2();

#endif