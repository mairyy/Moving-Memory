#include "menu.h"

void mainLayer(SDL_Renderer* gRenderer, SDL_Surface* gScreen, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    SDL_Surface* startBackGroundImage = loadImageFromFile("Pictures/startGameBackGround.png", gScreen);
    SDL_Texture* startBackGroundTexture = SDL_CreateTextureFromSurface(gRenderer, startBackGroundImage);
    applyImage(startBackGroundTexture, gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Surface* startButtonImage = loadImageFromFile("Pictures/start.png", gScreen);
    startButtonImage = deleteBackGroundImage(startButtonImage, 0, 0, 0);
    SDL_Texture* startButtonTexture = SDL_CreateTextureFromSurface(gRenderer, startButtonImage);
    applyImage(startButtonTexture, gRenderer, 470, 370, 150, 54);

    SDL_Surface* helpButtonImage = loadImageFromFile("Pictures/help.png", gScreen);
    helpButtonImage = deleteBackGroundImage(helpButtonImage, 0, 0, 0);
    SDL_Texture* helpButtonTexture = SDL_CreateTextureFromSurface(gRenderer, helpButtonImage);
    applyImage(helpButtonTexture, gRenderer, 470, 470, 150, 54);
    
    SDL_RenderPresent(gRenderer);
}

void helpLayer(SDL_Renderer* gRenderer, SDL_Surface* gScreen, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    SDL_Surface* helpImage = loadImageFromFile("Pictures/helpImage.png", gScreen);
    SDL_Texture* helpImageTexture = SDL_CreateTextureFromSurface(gRenderer, helpImage);
    applyImage(helpImageTexture, gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* backButtonIamge = loadImageFromFile("Pictures/back.png", gScreen);
    backButtonIamge = deleteBackGroundImage(backButtonIamge, 0, 0, 0);
    SDL_Texture* backButtonTexture = SDL_CreateTextureFromSurface(gRenderer, backButtonIamge);
    applyImage(backButtonTexture, gRenderer, 880, 630, 150, 54);
    SDL_Delay(300);
    SDL_RenderPresent(gRenderer);
}

void winLayer(Picture* pics, SDL_Surface* gScreen, SDL_Renderer* gRenderer, Mix_Chunk* gWin, int &level, int &totalPics){
    SDL_Surface* winPic = loadImageFromFile("Pictures/congrat.png", gScreen);
    deleteBackGroundImage(winPic, 0, 0, 0);
    SDL_Texture* winTexture = SDL_CreateTextureFromSurface(gRenderer, winPic);
    SDL_Surface* nextLevelPic = loadImageFromFile("Pictures/nextLevel.png", gScreen);
    deleteBackGroundImage(nextLevelPic, 0, 0, 0);
    SDL_Texture* nLevelTexture = SDL_CreateTextureFromSurface(gRenderer, nextLevelPic);
    if(level == 1){
        applyImage(nLevelTexture, gRenderer, 300, 130, 500, 400);
    }else{
        applyImage(winTexture, gRenderer, 300, 130, 500, 400);
    }
    SDL_Delay(400);
    SDL_RenderPresent(gRenderer);
    Mix_PlayChannel(-1, gWin, 0);
    for(int i = 0; i < totalPics; i++){
        pics[i].setFind(false);
    }
}