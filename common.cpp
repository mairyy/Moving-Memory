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

void loadText(SDL_Renderer* renderer, TTF_Font* font, string text, string textFont, int fontSize, Uint8 red, Uint8 green, Uint8 blue){
    if(TTF_Init() == -1){
        cout << "TTF Error: " << TTF_GetError() << endl;
    }else{
        font = TTF_OpenFont(textFont.c_str(), fontSize);
        if(font == NULL){
            cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        }else{
            SDL_Color textColor = {red, green, blue};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
        }
    }
}

void applyText(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, string text, int x, int y){
    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);
    srcRest.x = 0;
    srcRest.y = 0;
    desRect.x = x;
    desRect.y = y;
    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
}