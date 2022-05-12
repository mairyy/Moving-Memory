#include "level1.h"

void loadLevel1(Picture *pics, int &totalPics, SDL_Texture* pic0Texture, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer){
    totalPics = 3;
    SDL_Surface* backGround = loadImageFromFile("Pictures/gameBackGround.png", screen);
    SDL_Texture* backGroundTexture = SDL_CreateTextureFromSurface(renderer, backGround);
    applyImage(backGroundTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    const int totalPos = 6;
    Point posArr[totalPos] = {{110, 115}, {360, 115}, {610, 115}, {110, 365}, {360, 365}, {610, 365}};
    for(int i = 0; i < totalPos; i++){
        applyImage(pic0Texture, renderer, posArr[i].getX(), posArr[i].getY(), 190, 190);
    }
    SDL_Delay(300);
    SDL_RenderPresent(renderer);
    srand(time(0));
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
}

void playLevel1(SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin, SDL_Texture* pic0Texture, SDL_Texture* pic1Texture, SDL_Texture* pic2Texture, SDL_Texture* pic3Texture){
    if(!pics[0].getFind() && x > pics[0].getPos1().getX() && x < pics[0].getPos1().getX() + 190 && y > pics[0].getPos1().getY() && y < pics[0].getPos1().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);cout << pics[0].getPath() << endl;
        applyImage(pic1Texture, renderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[0].getPos1().getX() || prevPos.getY() != pics[0].getPos1().getY()){
            if(count == 0){
                count = 1;
                prevPath = pics[0].getPath();
                prevPos = pics[0].getPos1();
            }else{
                if(prevPath != pics[0].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    applyImage(pic0Texture, renderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
                    applyImage(pic0Texture, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[0].setFind(true);
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
            }
        }cout << count << endl;
    }
    if(!pics[0].getFind() && x > pics[0].getPos2().getX() && x < pics[0].getPos2().getX() + 190 && y > pics[0].getPos2().getY() && y < pics[0].getPos2().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);cout << pics[0].getPath() << endl;
        applyImage(pic1Texture, renderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[0].getPos2().getX() || prevPos.getY() != pics[0].getPos2().getY()){    
                if(count == 0){
                count = 1;
                prevPath = pics[0].getPath();
                prevPos = pics[0].getPos2();
            }else{
                if(prevPath != pics[0].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    applyImage(pic0Texture, renderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
                    applyImage(pic0Texture, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[0].setFind(true);
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
            }
        }cout << count << endl;
    }
    if(!pics[1].getFind() && x > pics[1].getPos1().getX() && x < pics[1].getPos1().getX() + 190 && y > pics[1].getPos1().getY() && y < pics[1].getPos1().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);cout << pics[1].getPath() << endl;
        applyImage(pic2Texture, renderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[1].getPos1().getX() || prevPos.getY() != pics[1].getPos1().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[1].getPath();
                prevPos = pics[1].getPos1();
            }else{
                if(prevPath != pics[1].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    applyImage(pic0Texture, renderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
                    applyImage(pic0Texture, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[1].setFind(true);
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
            }
        }cout << count << endl;
    }
    if(!pics[1].getFind() && x >  pics[1].getPos2().getX() && x < pics[1].getPos2().getX() + 190 && y > pics[1].getPos2().getY() && y < pics[1].getPos2().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);cout << pics[1].getPath() << endl;
        applyImage(pic2Texture, renderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[1].getPos2().getX() || prevPos.getY() != pics[1].getPos2().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[1].getPath();
                prevPos = pics[1].getPos2();
            }else{
                if(prevPath != pics[1].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    applyImage(pic0Texture, renderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
                    applyImage(pic0Texture, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[1].setFind(true);
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
            }
        }cout << count << endl;
    }
    if(!pics[2].getFind() && x > pics[2].getPos1().getX() && x < pics[2].getPos1().getX() + 190 && y > pics[2].getPos1().getY() && y < pics[2].getPos1().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);cout << pics[2].getPath() << endl;
        applyImage(pic3Texture, renderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[2].getPos1().getX() || prevPos.getY() != pics[2].getPos1().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[2].getPath();
                prevPos = pics[2].getPos1();
            }else{
                if(prevPath != pics[2].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    applyImage(pic0Texture, renderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
                    applyImage(pic0Texture, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[2].setFind(true);
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
            }
        }cout << count << endl;
    }
    if(!pics[2].getFind() && x > pics[2].getPos2().getX() && x < pics[2].getPos2().getX() + 190 && y > pics[2].getPos2().getY() && y < pics[2].getPos2().getY() + 190){
        Mix_PlayChannel(-1, gClick, 0);cout << pics[2].getPath() << endl;
        applyImage(pic3Texture, renderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[2].getPos2().getX() || prevPos.getY() != pics[2].getPos2().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[2].getPath();
                prevPos = pics[2].getPos2();
            }else{
                if(prevPath != pics[2].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    applyImage(pic0Texture, renderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
                    applyImage(pic0Texture, renderer, prevPos.getX(), prevPos.getY(), 190, 190);
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[2].setFind(true);
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
            }
        }cout << count << endl;
    }
}