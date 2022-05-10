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
Mix_Chunk* gClick = NULL;
Mix_Chunk* gWrong = NULL;
Mix_Chunk* gRight = NULL;
Mix_Chunk* gWin = NULL;

bool init();
void clean();

int main(int argc, char* args[]){
    int x, y;
    bool quit = false;
    if(!init()){
        cout << "Failed to initialize!\n";
    }else{
        gClick = Mix_LoadWAV("Sound-effects/soundClick.wav");
        gWrong = Mix_LoadWAV("Sound-effects/soundWrong.wav");
        gRight = Mix_LoadWAV("Sound-effects/soundRight.wav");
        gWin = Mix_LoadWAV("Sound-effects/soundWin.wav");
        SDL_Surface* backGround = loadImageFromFile("Pictures/gameBackGround.png", gScreen);
        SDL_Texture* backGroundTexture = SDL_CreateTextureFromSurface(gRenderer, backGround);
        applyImage(backGroundTexture, gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        const int totalPos = 6;
        Point posArr[totalPos] = {{110, 115}, {360, 115}, {610, 115}, {110, 365}, {360, 365}, {610, 365}};
        SDL_Surface* pic0 = loadImageFromFile("Pictures/0.png",gScreen);
        SDL_Texture* pic0Texture = SDL_CreateTextureFromSurface(gRenderer, pic0);
        for(int i = 0; i < totalPos; i++){
            applyImage(pic0Texture, gRenderer, posArr[i].getX(), posArr[i].getY(), 190, 190);
        }
        // SDL_Delay(300);
        SDL_RenderPresent(gRenderer);
        srand(time(0));
        const int totalPics = 3;
        Picture pics[totalPics];
        string picsPath[totalPics] = {"Pictures/1.png", "Pictures/2.png", "Pictures/3.png"};
        for(int i = 0; i < totalPics; i++){
            pics[i].setPath(picsPath[i]);
        }
        for(int i = 0; i < totalPos; i++){
            int k = rand() % + totalPics;
            if(pics[k].getFre() == 0){
                pics[k].setFre(1);
                pics[k].setPos1(posArr[i].getX(), posArr[i].getY());
            }else if(pics[k].getFre() == 1){
                pics[k].setFre(2);
                pics[k].setPos2(posArr[i].getX(), posArr[i].getY());
            }else{
                i--;
            }
        }
        SDL_Surface* pic1 = loadImageFromFile(pics[0].getPath(), gScreen);
        SDL_Texture* pic1Texture = SDL_CreateTextureFromSurface(gRenderer, pic1);
        SDL_Surface* pic2 = loadImageFromFile(pics[1].getPath(), gScreen);
        SDL_Texture* pic2Texture = SDL_CreateTextureFromSurface(gRenderer, pic2);
        SDL_Surface* pic3 = loadImageFromFile(pics[2].getPath(), gScreen);
        SDL_Texture* pic3Texture = SDL_CreateTextureFromSurface(gRenderer, pic3);
        string prevPath = "";
        Point prevPos = {0, 0};
        int count = 0;
        while(!quit){
            SDL_GetMouseState(&x, &y);
            while(SDL_PollEvent(&gEvent) != 0){
                if(gEvent.type == SDL_QUIT){
                    quit = true;
                }
                if(gEvent.type == SDL_MOUSEBUTTONDOWN){
                    if(!pics[0].getFind() && x > pics[0].getPos1().getX() && x < pics[0].getPos1().getX() + 190 && y > pics[0].getPos1().getY() && y < pics[0].getPos1().getY() + 190){
                        Mix_PlayChannel(-1, gClick, 0);
                        applyImage(pic1Texture, gRenderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(prevPos.getX() != pics[0].getPos1().getX() || prevPos.getY() != pics[0].getPos1().getY()){
                            if(count == 0){
                                count = 1;
                                prevPath = pics[0].getPath();
                                prevPos = pics[0].getPos1();
                            }else{
                                if(prevPath != pics[0].getPath()){
                                    Mix_PlayChannel(-1, gWrong, 0);
                                    applyImage(pic0Texture, gRenderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
                                    applyImage(pic0Texture, gRenderer, prevPos.getX(), prevPos.getY(), 190, 190);
                                    SDL_Delay(500);
                                    SDL_RenderPresent(gRenderer);
                                }else{
                                    Mix_PlayChannel(-1, gRight, 0);
                                    pics[0].setFind(true);
                                }
                                prevPath = "";
                                prevPos = {0,0};
                                count = 0;
                            }
                        }
                    }
                    if(!pics[0].getFind() && x > pics[0].getPos2().getX() && x < pics[0].getPos2().getX() + 190 && y > pics[0].getPos2().getY() && y < pics[0].getPos2().getY() + 190){
                        Mix_PlayChannel(-1, gClick, 0);
                        applyImage(pic1Texture, gRenderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(prevPos.getX() != pics[0].getPos2().getX() || prevPos.getY() != pics[0].getPos2().getY()){    
                                if(count == 0){
                                count = 1;
                                prevPath = pics[0].getPath();
                                prevPos = pics[0].getPos2();
                            }else{
                                if(prevPath != pics[0].getPath()){
                                    Mix_PlayChannel(-1, gWrong, 0);
                                    applyImage(pic0Texture, gRenderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
                                    applyImage(pic0Texture, gRenderer, prevPos.getX(), prevPos.getY(), 190, 190);
                                    SDL_Delay(500);
                                    SDL_RenderPresent(gRenderer);
                                }else{
                                    Mix_PlayChannel(-1, gRight, 0);
                                    pics[0].setFind(true);
                                }
                                prevPath = "";
                                prevPos = {0,0};
                                count = 0;
                            }
                        }
                    }
                    if(!pics[1].getFind() && x > pics[1].getPos1().getX() && x < pics[1].getPos1().getX() + 190 && y > pics[1].getPos1().getY() && y < pics[1].getPos1().getY() + 190){
                        Mix_PlayChannel(-1, gClick, 0);
                        applyImage(pic2Texture, gRenderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(prevPos.getX() != pics[1].getPos1().getX() || prevPos.getY() != pics[1].getPos1().getY()){    
                            if(count == 0){
                                count = 1;
                                prevPath = pics[1].getPath();
                                prevPos = pics[1].getPos1();
                            }else{
                                if(prevPath != pics[1].getPath()){
                                    Mix_PlayChannel(-1, gWrong, 0);
                                    applyImage(pic0Texture, gRenderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
                                    applyImage(pic0Texture, gRenderer, prevPos.getX(), prevPos.getY(), 190, 190);
                                    SDL_Delay(500);
                                    SDL_RenderPresent(gRenderer);
                                }else{
                                    Mix_PlayChannel(-1, gRight, 0);
                                    pics[1].setFind(true);
                                }
                                prevPath = "";
                                prevPos = {0,0};
                                count = 0;
                            }
                        }
                    }
                    if(!pics[1].getFind() && x >  pics[1].getPos2().getX() && x < pics[1].getPos2().getX() + 190 && y > pics[1].getPos2().getY() && y < pics[1].getPos2().getY() + 190){
                        Mix_PlayChannel(-1, gClick, 0);
                        applyImage(pic2Texture, gRenderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(prevPos.getX() != pics[1].getPos2().getX() || prevPos.getY() != pics[1].getPos2().getY()){    
                            if(count == 0){
                                count = 1;
                                prevPath = pics[1].getPath();
                                prevPos = pics[1].getPos2();
                            }else{
                                if(prevPath != pics[1].getPath()){
                                    Mix_PlayChannel(-1, gWrong, 0);
                                    applyImage(pic0Texture, gRenderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
                                    applyImage(pic0Texture, gRenderer, prevPos.getX(), prevPos.getY(), 190, 190);
                                    SDL_Delay(500);
                                    SDL_RenderPresent(gRenderer);
                                }else{
                                    Mix_PlayChannel(-1, gRight, 0);
                                    pics[1].setFind(true);
                                }
                                prevPath = "";
                                prevPos = {0,0};
                                count = 0;
                            }
                        }
                    }
                    if(!pics[2].getFind() && x > pics[2].getPos1().getX() && x < pics[2].getPos1().getX() + 190 && y > pics[2].getPos1().getY() && y < pics[2].getPos1().getY() + 190){
                        Mix_PlayChannel(-1, gClick, 0);
                        applyImage(pic3Texture, gRenderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(prevPos.getX() != pics[2].getPos1().getX() || prevPos.getY() != pics[2].getPos1().getY()){    
                            if(count == 0){
                                count = 1;
                                prevPath = pics[2].getPath();
                                prevPos = pics[2].getPos1();
                            }else{
                                if(prevPath != pics[2].getPath()){
                                    Mix_PlayChannel(-1, gWrong, 0);
                                    applyImage(pic0Texture, gRenderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
                                    applyImage(pic0Texture, gRenderer, prevPos.getX(), prevPos.getY(), 190, 190);
                                    SDL_Delay(500);
                                    SDL_RenderPresent(gRenderer);
                                }else{
                                    Mix_PlayChannel(-1, gRight, 0);
                                    pics[2].setFind(true);
                                }
                                prevPath = "";
                                prevPos = {0,0};
                                count = 0;
                            }
                        }
                    }
                    if(!pics[2].getFind() && x > pics[2].getPos2().getX() && x < pics[2].getPos2().getX() + 190 && y > pics[2].getPos2().getY() && y < pics[2].getPos2().getY() + 190){
                        Mix_PlayChannel(-1, gClick, 0);
                        applyImage(pic3Texture, gRenderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(prevPos.getX() != pics[2].getPos2().getX() || prevPos.getY() != pics[2].getPos2().getY()){    
                            if(count == 0){
                                count = 1;
                                prevPath = pics[2].getPath();
                                prevPos = pics[2].getPos2();
                            }else{
                                if(prevPath != pics[2].getPath()){
                                    Mix_PlayChannel(-1, gWrong, 0);
                                    applyImage(pic0Texture, gRenderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
                                    applyImage(pic0Texture, gRenderer, prevPos.getX(), prevPos.getY(), 190, 190);
                                    SDL_Delay(500);
                                    SDL_RenderPresent(gRenderer);
                                }else{
                                    Mix_PlayChannel(-1, gRight, 0);
                                    pics[2].setFind(true);
                                }
                                prevPath = "";
                                prevPos = {0,0};
                                count = 0;
                            }
                        }
                    }
                }
                if(pics[0].getFind() && pics[1].getFind() && pics[2].getFind()){
                    SDL_Surface* winPic = loadImageFromFile("Pictures/congrat.png", gScreen);
                    deleteBackGroundImage(winPic, 0, 0, 0);
                    SDL_Texture* winTexture = SDL_CreateTextureFromSurface(gRenderer, winPic);
                    applyImage(winTexture, gRenderer, 300, 130, 500, 400);
                    SDL_Delay(400);
                    SDL_RenderPresent(gRenderer);
                    Mix_PlayChannel(-1, gWin, 0);
                    pics[0].setFind(false);
                    pics[1].setFind(false);
                    pics[2].setFind(false);
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

void clean(){
    SDL_FreeSurface(gScreen);
    SDL_DestroyWindow(gWindow);
    SDL_DestroyTexture(gTexture);
    SDL_RenderClear(gRenderer);
    Mix_FreeChunk(gClick);
    Mix_FreeChunk(gWrong);
    Mix_FreeChunk(gRight);
    Mix_FreeChunk(gWin);
}