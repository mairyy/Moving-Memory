#include "common.h"

SDL_Surface* loadImageFromFile(string path, SDL_Surface* screen){
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizeImage = NULL;
    loadedImage = IMG_Load(path.c_str());
    if(loadedImage == NULL){
        cout << "Unable to load " << path.c_str() << "! SDL_image error: " << IMG_GetError() << endl;
    }else{
        optimizeImage = SDL_ConvertSurface(loadedImage, screen->format, 0);
        if(optimizeImage == NULL){
            cout << "Unable to optimize " << path.c_str() << "! SDL error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedImage);
    }
    return optimizeImage;
}

SDL_Surface* deleteBackGroundImage(SDL_Surface* image, Uint8 red, Uint8 green, Uint8 blue){
    SDL_Surface* newImage = image;
    UINT32 color_key = SDL_MapRGB(newImage->format, red, green, blue);
    SDL_SetColorKey(newImage, SDL_TRUE, color_key);
    return newImage;
}

void applyImage(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h){
    SDL_Rect desRect;
    desRect.x = x;
    desRect.y = y;
    desRect.w = w;
    desRect.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);
}

void loadScore(int &score, SDL_Renderer* gRenderer, TTF_Font* gFont, SDL_Texture* gTexture){
    gFont = TTF_OpenFont("Fonts/AsapSemiBold.ttf", 40);
	SDL_Color color = {255, 255, 255};
	string text = to_string(score);
	SDL_Surface* surface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	gTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(gFont, text.c_str(), &srcRest.w, &srcRest.h);
	srcRest.x = 0;
	srcRest.y =  0;
	desRect.x = 955;
	desRect.y = 350;
	desRect.w = srcRest.w;
	desRect.h = srcRest.h;
	SDL_RenderCopy(gRenderer, gTexture, &srcRest, &desRect);
    SDL_RenderPresent(gRenderer);
}

void loadHighScore(int &highScore, SDL_Renderer* gRenderer, TTF_Font* gFont, SDL_Texture* gTexture){
    gFont = TTF_OpenFont("Fonts/AsapSemiBold.ttf", 100);
	SDL_Color color = {255, 255, 255};
	string text = to_string(highScore);
	SDL_Surface* surface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	gTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(gFont, text.c_str(), &srcRest.w, &srcRest.h);
	srcRest.x = 0;
	srcRest.y =  0;
	desRect.x = 495;
	desRect.y = 250;
	desRect.w = srcRest.w;
	desRect.h = srcRest.h;
	SDL_RenderCopy(gRenderer, gTexture, &srcRest, &desRect);
}