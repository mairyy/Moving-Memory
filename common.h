#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

SDL_Surface* loadImageFromFile(string path, SDL_Surface* screen);
SDL_Surface* deleteBackGroundImage(SDL_Surface* image, Uint8 red, Uint8 green, Uint8 blue);
void applyImage(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);
void loadText(SDL_Renderer* renderer, TTF_Font* font, string text, string textFont, int fontSize, Uint8 red, Uint8 green, Uint8 blue);
void applyText(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, string text, int x, int y);

#endif