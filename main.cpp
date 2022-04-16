#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 700
#define SCREEN_BPP 32

SDL_Surface* gScreen = NULL;
SDL_Window* gWindow = NULL;
SDL_Event gEvent;
SDL_Texture* gTexture = NULL;
TTF_Font* gFont = NULL;
SDL_Renderer* gRenderer = NULL;

bool init();
SDL_Surface* loadImageFromFile(string path);
SDL_Surface* deleteBackGroundImage(SDL_Surface* image, Uint8 red, Uint8 green, Uint8 blue);
SDL_Texture* loadImageFromRenderedText(string textureText, SDL_Color textColor);
void applyImage(SDL_Texture* texture, int x, int y, int w, int h);
void loadText(string text, string textFont, int fontSize, Uint8 red, Uint8 green, Uint8 blue);
void applyText(string text, int x, int y);
void clean();

int main(int argc, char* args[]){
    bool quit = false;
    if(!init()){
        cout << "Failed to initialize!\n";
    }else{
        SDL_Surface* startBackGroundImage = loadImageFromFile("Pictures/startGameBackGround.png");
        SDL_Texture* startBackGroundTexture = SDL_CreateTextureFromSurface(gRenderer, startBackGroundImage);
        applyImage(startBackGroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_Surface* startButtonImage = loadImageFromFile("Pictures/start.png");
        startButtonImage = deleteBackGroundImage(startButtonImage, 0, 0, 0);
        SDL_Texture* startButtonTexture = SDL_CreateTextureFromSurface(gRenderer, startButtonImage);
        applyImage(startButtonTexture, 470, 370, 150, 54);

        SDL_Surface* helpButtonImage = loadImageFromFile("Pictures/help.png");
        helpButtonImage = deleteBackGroundImage(helpButtonImage, 0, 0, 0);
        SDL_Texture* helpButtonTexture = SDL_CreateTextureFromSurface(gRenderer, helpButtonImage);
        applyImage(helpButtonTexture, 470, 470, 150, 54);
        while(!quit){
            while(SDL_PollEvent(&gEvent) != 0){
                if(gEvent.type == SDL_QUIT){
                    quit = true;
                }
            }
            SDL_RenderPresent(gRenderer);
        }
    }
    clean();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }else{
        gWindow = SDL_CreateWindow("Moving Memory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }else{
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL){
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl; 
            }else{
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }else{
                    gScreen = SDL_GetWindowSurface(gWindow);
                }
            }
        }
    }
    return success;
}

SDL_Surface* loadImageFromFile(string path){
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizeImage = NULL;
    loadedImage = IMG_Load(path.c_str());
    if(loadedImage == NULL){
        cout << "Unable to load " << path.c_str() << "! SDL_image error: " << IMG_GetError() << endl;
    }else{
        optimizeImage = SDL_ConvertSurface(loadedImage, gScreen->format, 0);
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

void applyImage(SDL_Texture* texture, int x, int y, int w, int h){
    SDL_Rect desRect;
    desRect.x = x;
    desRect.y = y;
    desRect.w = w;
    desRect.h = h;
    SDL_RenderCopy(gRenderer, texture, NULL, &desRect);
}

void loadText(string text, string textFont, int fontSize, Uint8 red, Uint8 green, Uint8 blue){
    if(TTF_Init() == -1){
        cout << "TTF Error: " << TTF_GetError() << endl;
    }else{
        gFont = TTF_OpenFont(textFont.c_str(), fontSize);
        if(gFont == NULL){
            cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        }else{
            SDL_Color textColor = {red, green, blue};
            SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
            gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            SDL_FreeSurface(textSurface);
        }
    }
}

void applyText(string text, int x, int y){
    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(gFont, text.c_str(), &srcRest.w, &srcRest.h);
    srcRest.x = 0;
    srcRest.y = 0;
    desRect.x = x;
    desRect.y = y;
    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(gRenderer, gTexture, &srcRest, &desRect);
}

void clean(){
    SDL_FreeSurface(gScreen);
    SDL_DestroyWindow(gWindow);
    SDL_DestroyTexture(gTexture);
}