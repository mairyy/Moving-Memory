#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include "common.h"
#include "pictures.h"
#include "level1.h"
#include "menu.h"

using namespace std;

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 700
#define SCREEN_BPP 32

SDL_Surface* gScreen = NULL;
SDL_Window* gWindow = NULL;
SDL_Event gEvent;
TTF_Font* gFont = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Chunk* gClick = NULL;
Mix_Chunk* gWrong = NULL;
Mix_Chunk* gRight = NULL;
Mix_Chunk* gWin = NULL;
SDL_Texture* pic0Texture = NULL, *pic1Texture = NULL, *pic2Texture = NULL, *pic3Texture = NULL;

bool init();
void loadLevel1Picture(Picture* pics);
void clean();

int main(int argc, char* args[]){
    int x, y;
    bool isQuit = false, isWin = false, isStart = false, isHelp = false;
    if(!init()){
        cout << "Failed to initialize!\n";
    }else{
        gClick = Mix_LoadWAV("Sound-effects/soundClick.wav");
        gWrong = Mix_LoadWAV("Sound-effects/soundWrong.wav");
        gRight = Mix_LoadWAV("Sound-effects/soundRight.wav");
        gWin = Mix_LoadWAV("Sound-effects/soundWin.wav");
        SDL_Surface* pic0 = loadImageFromFile("Pictures/0.png",gScreen);
        pic0Texture = SDL_CreateTextureFromSurface(gRenderer, pic0);
        int totalPics;
        Picture pics[10];
        string prevPath = "";
        Point prevPos = {0, 0};
        int count = 0;
        mainLayer(gRenderer,gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
        while(!isQuit){
            SDL_GetMouseState(&x, &y);
            while(SDL_PollEvent(&gEvent) != 0){
                if(gEvent.type == SDL_QUIT){
                    isQuit = true;
                }
                if(isStart){
                    if(gEvent.type == SDL_MOUSEBUTTONDOWN && !isWin){
                        playLevel1(gRenderer, pics, x, y, count, prevPath, prevPos, gClick, gWrong, gRight, gWin, pic0Texture, pic1Texture, pic2Texture, pic3Texture);
                    }
                    if(pics[0].getFind() && pics[1].getFind() && pics[2].getFind()){
                        winLayer(pics, gScreen, gRenderer, gWin);
                        isWin = true;
                    }
                }
                if(!isStart){
                    if(gEvent.type == SDL_MOUSEBUTTONDOWN){
                        if(x > 470 && x < 620 && y > 470 && y < 524){
                            Mix_PlayChannel(-1, gClick, 0);
                            helpLayer(gRenderer, gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
                            isHelp = true;
                        }
                        if(x > 470 && x < 470+150 && y > 370 && y < 370+54){
                            Mix_PlayChannel(-1, gClick, 0);
                            loadLevel1(pics, totalPics, pic0Texture, SCREEN_WIDTH, SCREEN_HEIGHT, gScreen, gRenderer);
                            loadLevel1Picture(pics);
                            isStart = true;
                        }
                        if(x > 880 && x < 880+150 && y > 630 && y < 630+54 && isHelp){
                            Mix_PlayChannel(-1, gClick, 0);
                            mainLayer(gRenderer, gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
                            isHelp = false;
                        }
                    }
                }
                
            }
        }
    }
    clean();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    return 0;
}

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
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
                }else if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
                    success = false;
                }else{
                    gScreen = SDL_GetWindowSurface(gWindow);
                }
            }
        }
    }
    return success;
}

void loadLevel1Picture(Picture* pics){
    SDL_Surface* pic1 = loadImageFromFile(pics[0].getPath(),gScreen);
    pic1Texture = SDL_CreateTextureFromSurface(gRenderer, pic1);
    SDL_Surface* pic2 = loadImageFromFile(pics[1].getPath(), gScreen);
    pic2Texture = SDL_CreateTextureFromSurface(gRenderer, pic2);
    SDL_Surface* pic3 = loadImageFromFile(pics[2].getPath(), gScreen);
    pic3Texture = SDL_CreateTextureFromSurface(gRenderer, pic3);
}

void clean(){
    SDL_FreeSurface(gScreen);
    SDL_DestroyWindow(gWindow);
    SDL_RenderClear(gRenderer);
    Mix_FreeChunk(gClick);
    Mix_FreeChunk(gWrong);
    Mix_FreeChunk(gRight);
    Mix_FreeChunk(gWin);
    SDL_DestroyTexture(pic0Texture);
    SDL_DestroyTexture(pic1Texture);
    SDL_DestroyTexture(pic2Texture);
    SDL_DestroyTexture(pic3Texture);
}