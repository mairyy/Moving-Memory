#ifndef LEVEL3_H
#define LEVEL3_H

#include "common.h"
#include "pictures.h"
#include <SDL_mixer.h>

static SDL_Texture* pic0Texture3 = NULL, *pic1Texture3 = NULL, *pic2Texture3 = NULL, *pic3Texture3 = NULL, *pic4Texture3 = NULL, *pic5Texture3 = NULL, *xTexture3 = NULL;
static SDL_Texture* scoreTexture3 = NULL;

void loadPictures3(Picture *pics, SDL_Renderer* gRenderer, SDL_Surface* gScreen);
void loadLevel3(int &level, Picture *pics, int &totalPics, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer);
void playLevel3(SDL_Surface* gScreen,  SDL_Texture* gTexture, TTF_Font* gFont, int &score, SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin);
void clean3();

#endif