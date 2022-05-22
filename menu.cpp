#include "menu.h"
#include "common.h"

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
    
    SDL_Surface* highScoreButtonImage = loadImageFromFile("Pictures/highScore.png", gScreen);
    highScoreButtonImage = deleteBackGroundImage(highScoreButtonImage, 0, 0, 0);
    SDL_Texture* highScoreButtonTexture = SDL_CreateTextureFromSurface(gRenderer, highScoreButtonImage);
    applyImage(highScoreButtonTexture, gRenderer, 470, 570, 150, 54);

    SDL_FreeSurface(startBackGroundImage);
    SDL_FreeSurface(startButtonImage);
    SDL_FreeSurface(helpButtonImage);
    SDL_FreeSurface(highScoreButtonImage);

    SDL_RenderPresent(gRenderer);
}

void helpLayer(SDL_Renderer* gRenderer, SDL_Surface* gScreen, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    SDL_Surface* helpImage = loadImageFromFile("Pictures/helpImage.png", gScreen);
    SDL_Texture* helpImageTexture = SDL_CreateTextureFromSurface(gRenderer, helpImage);
    applyImage(helpImageTexture, gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* backButtonImage = loadImageFromFile("Pictures/back.png", gScreen);
    backButtonImage = deleteBackGroundImage(backButtonImage, 0, 0, 0);
    SDL_Texture* backButtonTexture = SDL_CreateTextureFromSurface(gRenderer, backButtonImage);
    applyImage(backButtonTexture, gRenderer, 880, 630, 150, 54);
    SDL_FreeSurface(helpImage);
    SDL_FreeSurface(backButtonImage);
    SDL_Delay(300);
    SDL_RenderPresent(gRenderer);
}

void winLayer(Picture* pics, SDL_Surface* gScreen, SDL_Renderer* gRenderer, Mix_Chunk* gWin, int &level, int &totalPics){
    SDL_Surface* winPic = loadImageFromFile("Pictures/congrat.png", gScreen);
    winPic = deleteBackGroundImage(winPic, 0, 0, 0);
    SDL_Texture* winTexture = SDL_CreateTextureFromSurface(gRenderer, winPic);
    SDL_Surface* nextLevelPic = loadImageFromFile("Pictures/nextLevel.png", gScreen);
    nextLevelPic = deleteBackGroundImage(nextLevelPic, 0, 0, 0);
    SDL_Texture* nLevelTexture = SDL_CreateTextureFromSurface(gRenderer, nextLevelPic);
    if(level == 1 || level == 2){
        applyImage(nLevelTexture, gRenderer, 300, 130, 500, 400);
    }else{
        applyImage(winTexture, gRenderer, 300, 130, 500, 400);
    }
    SDL_FreeSurface(winPic);
    SDL_FreeSurface(nextLevelPic);
    SDL_Delay(400);
    SDL_RenderPresent(gRenderer);
    Mix_PlayChannel(-1, gWin, 0);
    for(int i = 0; i < totalPics; i++){
        pics[i].setFind(false);
    }
}

void highScoreLayer(SDL_Renderer* gRenderer, SDL_Surface* gScreen, int SCREEN_WIDTH, int SCREEN_HEIGHT, int &highScore){
    SDL_Surface* highScoreImage = loadImageFromFile("Pictures/highScoreImage.png", gScreen);
    SDL_Texture* highScoreImageTexture = SDL_CreateTextureFromSurface(gRenderer, highScoreImage);
    applyImage(highScoreImageTexture, gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* backButtonIamge = loadImageFromFile("Pictures/back.png", gScreen);
    backButtonIamge = deleteBackGroundImage(backButtonIamge, 0, 0, 0);
    SDL_Texture* backButtonTexture = SDL_CreateTextureFromSurface(gRenderer, backButtonIamge);
    applyImage(backButtonTexture, gRenderer, 880, 630, 150, 54);
    TTF_Font* gFont = NULL;
    SDL_Texture* gTexture = NULL;
    loadHighScore(highScore, gRenderer, gFont, gTexture);
    SDL_FreeSurface(highScoreImage);
    SDL_FreeSurface(backButtonIamge);
    SDL_Delay(300);
    SDL_RenderPresent(gRenderer);
}