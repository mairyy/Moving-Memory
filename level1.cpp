#include "level1.h"

void loadPictures1(Picture* pics, SDL_Renderer* gRenderer, SDL_Surface* gScreen){
    SDL_Surface* pic0 = loadImageFromFile("Pictures/0.png",gScreen);
    pic0Texture1 = SDL_CreateTextureFromSurface(gRenderer, pic0);
    SDL_Surface* pic1 = loadImageFromFile(pics[0].getPath(),gScreen);
    pic1Texture1 = SDL_CreateTextureFromSurface(gRenderer, pic1);
    SDL_Surface* pic2 = loadImageFromFile(pics[1].getPath(), gScreen);
    pic2Texture1 = SDL_CreateTextureFromSurface(gRenderer, pic2);
    SDL_Surface* pic3 = loadImageFromFile(pics[2].getPath(), gScreen);
    pic3Texture1 = SDL_CreateTextureFromSurface(gRenderer, pic3);
    SDL_Surface* pic = loadImageFromFile("Pictures/score.png", gScreen);
    deleteBackGroundImage(pic, 0, 0, 0);
    scoreTexture1 = SDL_CreateTextureFromSurface(gRenderer, pic);
    SDL_FreeSurface(pic0);
    SDL_FreeSurface(pic1);
    SDL_FreeSurface(pic2);
    SDL_FreeSurface(pic3);
    SDL_FreeSurface(pic);
}

void loadLevel1(int &level, Picture *pics, int &totalPics, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer){
    level = 1;
    totalPics = 3;
    const int totalPos = 6;
    Point posArr[totalPos] = {{110, 115}, {360, 115}, {610, 115}, {110, 365}, {360, 365}, {610, 365}};
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
    SDL_Surface* backGround = loadImageFromFile("Pictures/level1.png", screen);
    SDL_Texture* backGroundTexture = SDL_CreateTextureFromSurface(renderer, backGround);
    applyImage(backGroundTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_FreeSurface(backGround);
    for(int i = 0; i < totalPos; i++){
        applyImage(pic0Texture1, renderer, posArr[i].getX(), posArr[i].getY(), 190, 190);
    }
    applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
    SDL_Delay(300);
    SDL_RenderPresent(renderer);
}

void playLevel1(SDL_Surface* gScreen,  SDL_Texture* gTexture, TTF_Font* gFont, int &score, SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin){
    int point = 100;
    if(!pics[0].getFind() && x > pics[0].getPos1().getX() && x < pics[0].getPos1().getX() + 190 && y > pics[0].getPos1().getY() && y < pics[0].getPos1().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic1Texture1, renderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[0].getPos1().getX() || prevPos.getY() != pics[0].getPos1().getY()){
            if(count == 0){
                count = 1;
                prevPath = pics[0].getPath();
                prevPos = pics[0].getPos1();
            }else{
                if(prevPath != pics[0].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[0].getFirstClick1()) score -= point;
                    applyImage(pic0Texture1, renderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
                    applyImage(pic0Texture1, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[0].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[0].setFirstClick1(false);
    }
    if(!pics[0].getFind() && x > pics[0].getPos2().getX() && x < pics[0].getPos2().getX() + 190 && y > pics[0].getPos2().getY() && y < pics[0].getPos2().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic1Texture1, renderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[0].getPos2().getX() || prevPos.getY() != pics[0].getPos2().getY()){    
                if(count == 0){
                count = 1;
                prevPath = pics[0].getPath();
                prevPos = pics[0].getPos2();
            }else{
                if(prevPath != pics[0].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[0].getFirstClick2()) score -= point;
                    applyImage(pic0Texture1, renderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
                    applyImage(pic0Texture1, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[0].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[0].setFirstClick2(false);
    }
    if(!pics[1].getFind() && x > pics[1].getPos1().getX() && x < pics[1].getPos1().getX() + 190 && y > pics[1].getPos1().getY() && y < pics[1].getPos1().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic2Texture1, renderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[1].getPos1().getX() || prevPos.getY() != pics[1].getPos1().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[1].getPath();
                prevPos = pics[1].getPos1();
            }else{
                if(prevPath != pics[1].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[1].getFirstClick1()) score -= point;
                    applyImage(pic0Texture1, renderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
                    applyImage(pic0Texture1, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[1].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[1].setFirstClick1(false);
    }
    if(!pics[1].getFind() && x >  pics[1].getPos2().getX() && x < pics[1].getPos2().getX() + 190 && y > pics[1].getPos2().getY() && y < pics[1].getPos2().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic2Texture1, renderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[1].getPos2().getX() || prevPos.getY() != pics[1].getPos2().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[1].getPath();
                prevPos = pics[1].getPos2();
            }else{
                if(prevPath != pics[1].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[1].getFirstClick2()) score -= point;
                    applyImage(pic0Texture1, renderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
                    applyImage(pic0Texture1, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[1].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[1].setFirstClick2(false);
    }
    if(!pics[2].getFind() && x > pics[2].getPos1().getX() && x < pics[2].getPos1().getX() + 190 && y > pics[2].getPos1().getY() && y < pics[2].getPos1().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic3Texture1, renderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[2].getPos1().getX() || prevPos.getY() != pics[2].getPos1().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[2].getPath();
                prevPos = pics[2].getPos1();
            }else{
                if(prevPath != pics[2].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[2].getFirstClick1()) score -= point;
                    applyImage(pic0Texture1, renderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
                    applyImage(pic0Texture1, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[2].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[2].setFirstClick1(false);
    }
    if(!pics[2].getFind() && x > pics[2].getPos2().getX() && x < pics[2].getPos2().getX() + 190 && y > pics[2].getPos2().getY() && y < pics[2].getPos2().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic3Texture1, renderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[2].getPos2().getX() || prevPos.getY() != pics[2].getPos2().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[2].getPath();
                prevPos = pics[2].getPos2();
            }else{
                if(prevPath != pics[2].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[2].getFirstClick2()) score -= point;
                    applyImage(pic0Texture1, renderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
                    applyImage(pic0Texture1, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[2].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture1, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[2].setFirstClick2(false);
    }
}

void clean1(){
    SDL_DestroyTexture(pic0Texture1);
    SDL_DestroyTexture(pic1Texture1);
    SDL_DestroyTexture(pic2Texture1);
    SDL_DestroyTexture(pic3Texture1);
    SDL_DestroyTexture(scoreTexture1);
}