#include <SDL_mixer.h>
#include <cmath>
#include <ctime>
#include <fstream>
#include "common.h"
#include "pictures.h"
#include "level1.h"
#include "menu.h"
#include "level2.h"
#include "level3.h"

using namespace std;

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 700

SDL_Surface* gScreen = NULL;
SDL_Window* gWindow = NULL;
SDL_Event gEvent;
TTF_Font* gFont = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
Mix_Chunk* gClick = NULL;
Mix_Chunk* gWrong = NULL;
Mix_Chunk* gRight = NULL;
Mix_Chunk* gWin = NULL;
SDL_Texture* xTexture = NULL;

bool init();
void loadPictures(Picture* pics);
void close();

int main(int argc, char* args[]){
    int x, y, level = 1;
    bool isQuit = false, isWin = false, isStart = false, isHelp = false, isScore = false;
    if(!init()){
        cout << "Failed to initialize!\n";
    }else{
        int highScore;
        ifstream infile;
        infile.open("highScore.txt");
        infile >> highScore;
        infile.close();
        srand(time(0));
        gClick = Mix_LoadWAV("Sound-effects/soundClick.wav");
        gWrong = Mix_LoadWAV("Sound-effects/soundWrong.wav");
        gRight = Mix_LoadWAV("Sound-effects/soundRight.wav");
        gWin = Mix_LoadWAV("Sound-effects/soundWin.wav");
        int totalPics, score = 0;
        Picture pics[10];
        loadPictures(pics);
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
                    if(gEvent.type == SDL_MOUSEBUTTONDOWN){
                        if(!isWin){
                            if(level == 1){
                                playLevel1(gScreen, gTexture, gFont, score, gRenderer, pics, x, y, count, prevPath, prevPos, gClick, gWrong, gRight, gWin);
                            }else if (level == 2){
                                playLevel2(gScreen, gTexture, gFont, score, gRenderer, pics, x, y, count, prevPath, prevPos, gClick, gWrong, gRight, gWin);
                            }else{
                                playLevel3(gScreen, gTexture, gFont, score, gRenderer, pics, x, y, count, prevPath, prevPos, gClick, gWrong, gRight, gWin);
                            }
                        }
                    }
                    if(level == 1 && pics[0].getFind() && pics[1].getFind() && pics[2].getFind()){
                        winLayer(pics, gScreen, gRenderer, gWin, level, totalPics);
                        for(int i = 0; i < totalPics; i++){
                            pics[i].setFre(0);
                            pics[i].setPos1(0, 0);
                            pics[i].setPos2(0, 0);
                            pics[i].setFirstClick1(true);
                            pics[i].setFirstClick2(true);
                        }
                        count = 0;
                        prevPath = "";
                        prevPos = {0, 0};
                        loadLevel2(level, pics, totalPics, SCREEN_WIDTH, SCREEN_HEIGHT, gScreen, gRenderer);
                        loadScore(score, gRenderer, gFont, gTexture);
                    }
                    if(level == 2 && pics[0].getFind() && pics[1].getFind() && pics[2].getFind() && pics[3].getFind()){
                        applyImage(xTexture, gRenderer, pics[4].getPos1().getX(), pics[4].getPos1().getY(), 180, 180);
                        winLayer(pics, gScreen, gRenderer, gWin, level, totalPics);
                        for(int i = 0; i < totalPics; i++){
                            pics[i].setFre(0);
                            pics[i].setPos1(0, 0);
                            pics[i].setPos2(0, 0);
                            pics[i].setFirstClick1(true);
                            pics[i].setFirstClick2(true);
                        }
                        count = 0;
                        prevPath = "";
                        prevPos = {0, 0};
                        loadLevel3(level, pics, totalPics, SCREEN_WIDTH, SCREEN_HEIGHT, gScreen, gRenderer);
                        loadScore(score, gRenderer, gFont, gTexture);
                    }
                    if(level == 3 && pics[0].getFind() && pics[1].getFind() && pics[2].getFind() && pics[3].getFind() && pics[5].getFind()){
                        applyImage(xTexture, gRenderer, pics[4].getPos1().getX(), pics[4].getPos1().getY(), 175, 175);
                        applyImage(xTexture, gRenderer, pics[4].getPos2().getX(), pics[4].getPos2().getY(), 175, 175);
                        winLayer(pics, gScreen, gRenderer, gWin, level, totalPics);
                        isWin = true;                        
                    }
                }
                if(!isStart){
                    if(gEvent.type == SDL_MOUSEBUTTONDOWN){
                        if(x > 470 && x < 620 && y > 470 && y < 524 && !isHelp && !isScore){
                            Mix_PlayChannel(-1, gClick, 0);
                            helpLayer(gRenderer, gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
                            isHelp = true;
                        }
                        if(x > 470 && x < 470+150 && y > 370 && y < 370+54 && !isHelp){
                            Mix_PlayChannel(-1, gClick, 0);
                            loadLevel1(level, pics, totalPics, SCREEN_WIDTH, SCREEN_HEIGHT, gScreen, gRenderer);
                            loadScore(score, gRenderer, gFont, gTexture);
                            isStart = true;
                        }
                        if(x > 880 && x < 880+150 && y > 630 && y < 630+54 && (isHelp || isScore)){
                            Mix_PlayChannel(-1, gClick, 0);
                            mainLayer(gRenderer, gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
                            isHelp = false;
                            isScore = false;
                        }
                        if(x > 470 && x < 620 && y > 570 && y < 624 && !isScore && !isHelp){
                            Mix_PlayChannel(-1, gClick, 0);
                            highScoreLayer(gRenderer, gScreen, SCREEN_WIDTH, SCREEN_HEIGHT, highScore);
                            isScore = true;
                        }
                    }
                }
            }
        }
        if(score >= highScore){
            ofstream outfile;
            outfile.open("highScore.txt");
            outfile << score;
            outfile.close();
        }
    }
    close();
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
                }else if(TTF_Init() == -1){
                    cout << "TTF Error: " << TTF_GetError() << endl;
                    success = false;
                }else{
                    gScreen = SDL_GetWindowSurface(gWindow);
                }
            }
        }
    }
    return success;
}

void loadPictures(Picture* pics){
    int totalPics = 6;
    string picsPath[totalPics] = {"Pictures/1.png", "Pictures/2.png", "Pictures/3.png", "Pictures/4.png", "Pictures/x.png", "Pictures/5.png"};
    for(int i = 0; i < totalPics; i++){
        pics[i].setPath(picsPath[i]);
    }
    loadPictures1(pics, gRenderer, gScreen);
    loadPictures2(pics, gRenderer, gScreen);
    loadPictures3(pics, gRenderer, gScreen);
    SDL_Surface* x = loadImageFromFile(pics[4].getPath(), gScreen);
    xTexture = SDL_CreateTextureFromSurface(gRenderer, x);
}

void close(){
    SDL_FreeSurface(gScreen);
    SDL_DestroyWindow(gWindow);
    SDL_RenderClear(gRenderer);
    SDL_DestroyTexture(gTexture);
    Mix_FreeChunk(gClick);
    Mix_FreeChunk(gWrong);
    Mix_FreeChunk(gRight);
    Mix_FreeChunk(gWin);
    SDL_DestroyTexture(xTexture);
    clean1();
    clean2();
    clean3();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}