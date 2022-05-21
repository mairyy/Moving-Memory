#include "level3.h"

void loadPictures3(Picture *pics, SDL_Renderer* gRenderer, SDL_Surface* gScreen){
    SDL_Surface* pic0 = loadImageFromFile("Pictures/0.png",gScreen);
    pic0Texture3 = SDL_CreateTextureFromSurface(gRenderer, pic0);
    SDL_Surface* pic1 = loadImageFromFile(pics[0].getPath(),gScreen);
    pic1Texture3 = SDL_CreateTextureFromSurface(gRenderer, pic1);
    SDL_Surface* pic2 = loadImageFromFile(pics[1].getPath(), gScreen);
    pic2Texture3 = SDL_CreateTextureFromSurface(gRenderer, pic2);
    SDL_Surface* pic3 = loadImageFromFile(pics[2].getPath(), gScreen);
    pic3Texture3 = SDL_CreateTextureFromSurface(gRenderer, pic3);
    SDL_Surface* pic4 = loadImageFromFile(pics[3].getPath(), gScreen);
    pic4Texture3 = SDL_CreateTextureFromSurface(gRenderer, pic4);
    SDL_Surface* x = loadImageFromFile(pics[4].getPath(), gScreen);
    xTexture3 = SDL_CreateTextureFromSurface(gRenderer, x);
    SDL_Surface* pic5 = loadImageFromFile(pics[5].getPath(), gScreen);
    pic5Texture3 = SDL_CreateTextureFromSurface(gRenderer, pic5);
    SDL_Surface* pic = loadImageFromFile("Pictures/score.png", gScreen);
    deleteBackGroundImage(pic, 0, 0, 0);
    scoreTexture3 = SDL_CreateTextureFromSurface(gRenderer, pic);
    SDL_FreeSurface(pic0);
    SDL_FreeSurface(pic1);
    SDL_FreeSurface(pic2);
    SDL_FreeSurface(pic3);
    SDL_FreeSurface(pic4);
    SDL_FreeSurface(pic5);
    SDL_FreeSurface(x);
    SDL_FreeSurface(pic);
}

void loadLevel3(int &level, Picture *pics, int &totalPics, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Surface* screen, SDL_Renderer* renderer){
    level = 3;
    totalPics = 6;
    const int totalPos = 12;
    Point posArr[totalPos] = {{50, 40}, {265, 40}, {480, 40}, {695, 40}, {50, 255}, {265, 255}, {480, 255}, {695, 255}, {50, 475}, {265, 475}, {480, 475}, {695, 475}};
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
    SDL_Surface* backGround = loadImageFromFile("Pictures/level3.png", screen);
    SDL_Texture* backGroundTexture = SDL_CreateTextureFromSurface(renderer, backGround);
    applyImage(backGroundTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    for(int i = 0; i < totalPos; i++){
        applyImage(pic0Texture3, renderer, posArr[i].getX(), posArr[i].getY(), 175, 175);
    }
    applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
    SDL_Delay(3000);
    SDL_RenderPresent(renderer);
}

void playLevel3(SDL_Surface* gScreen,  SDL_Texture* gTexture, TTF_Font* gFont, int &score, SDL_Renderer* renderer, Picture* pics, int &x, int &y, int &count, string &prevPath, Point &prevPos, Mix_Chunk* gClick, Mix_Chunk* gWrong, Mix_Chunk* gRight, Mix_Chunk* gWin){
    int point = 100;
    if(!pics[0].getFind() && x > pics[0].getPos1().getX() && x < pics[0].getPos1().getX() + 175 && y > pics[0].getPos1().getY() && y < pics[0].getPos1().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic1Texture3, renderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 175, 175);
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
                    applyImage(pic0Texture3, renderer, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
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
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[0].setFirstClick1(false);
    }
    if(!pics[0].getFind() && x > pics[0].getPos2().getX() && x < pics[0].getPos2().getX() + 175 && y > pics[0].getPos2().getY() && y < pics[0].getPos2().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic1Texture3, renderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 175, 175);
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
                    applyImage(pic0Texture3, renderer, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
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
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[0].setFirstClick2(false);
    }
    if(!pics[1].getFind() && x > pics[1].getPos1().getX() && x < pics[1].getPos1().getX() + 175 && y > pics[1].getPos1().getY() && y < pics[1].getPos1().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic2Texture3, renderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 175, 175);
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
                    applyImage(pic0Texture3, renderer, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
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
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[1].setFirstClick1(false);
    }
    if(!pics[1].getFind() && x >  pics[1].getPos2().getX() && x < pics[1].getPos2().getX() + 175 && y > pics[1].getPos2().getY() && y < pics[1].getPos2().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic2Texture3, renderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 175, 175);
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
                    applyImage(pic0Texture3, renderer, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
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
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[1].setFirstClick2(false);
    }
    if(!pics[2].getFind() && x > pics[2].getPos1().getX() && x < pics[2].getPos1().getX() + 175 && y > pics[2].getPos1().getY() && y < pics[2].getPos1().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic3Texture3, renderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 175, 175);
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
                    applyImage(pic0Texture3, renderer, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
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
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[2].setFirstClick1(false);
    }
    if(!pics[2].getFind() && x > pics[2].getPos2().getX() && x < pics[2].getPos2().getX() + 175 && y > pics[2].getPos2().getY() && y < pics[2].getPos2().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic3Texture3, renderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 175, 175);
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
                    applyImage(pic0Texture3, renderer, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
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
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[2].setFirstClick2(false);
    }
    if(!pics[3].getFind() && x > pics[3].getPos1().getX() && x < pics[3].getPos1().getX() + 175 && y > pics[3].getPos1().getY() && y < pics[3].getPos1().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic4Texture3, renderer, pics[3].getPos1().getX(), pics[3].getPos1().getY(), 175, 175);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[3].getPos1().getX() || prevPos.getY() != pics[3].getPos1().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[3].getPath();
                prevPos = pics[3].getPos1();
            }else{
                if(prevPath != pics[3].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[3].getFirstClick1()) score -= point;
                    applyImage(pic0Texture3, renderer, pics[3].getPos1().getX(), pics[3].getPos1().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[3].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[3].setFirstClick1(false);
    }
    if(!pics[3].getFind() && x > pics[3].getPos2().getX() && x < pics[3].getPos2().getX() + 175 && y > pics[3].getPos2().getY() && y < pics[3].getPos2().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic4Texture3, renderer, pics[3].getPos2().getX(), pics[3].getPos2().getY(), 175, 175);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[3].getPos2().getX() || prevPos.getY() != pics[3].getPos2().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[3].getPath();
                prevPos = pics[3].getPos2();
            }else{
                if(prevPath != pics[3].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[3].getFirstClick2()) score -= point;
                    applyImage(pic0Texture3, renderer, pics[3].getPos2().getX(), pics[3].getPos2().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[3].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[3].setFirstClick2(false);
    }
    if(!pics[4].getFind() && x > pics[4].getPos1().getX() && x < pics[4].getPos1().getX() + 175 && y > pics[4].getPos1().getY() && y < pics[4].getPos1().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(xTexture3, renderer, pics[4].getPos1().getX(), pics[4].getPos1().getY(), 175, 175);
        SDL_RenderPresent(renderer);
        Mix_PlayChannel(-1, gWrong, 0);
        score -= point;
        applyImage(pic0Texture3, renderer, pics[4].getPos1().getX(), pics[4].getPos1().getY(), 175, 175);
        if(prevPos.getX() != 0 || prevPos.getY() != 0){
            applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
        }
        SDL_Delay(500);
        SDL_RenderPresent(renderer);
        prevPath = "";
        prevPos = {0,0};
        count = 0;
        applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
        SDL_RenderPresent(renderer);
        loadScore(score, renderer, gFont, gTexture);
    }
    if(!pics[4].getFind() && x > pics[4].getPos2().getX() && x < pics[4].getPos2().getX() + 175 && y > pics[4].getPos2().getY() && y < pics[4].getPos2().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(xTexture3, renderer, pics[4].getPos2().getX(), pics[4].getPos2().getY(), 175, 175);
        SDL_RenderPresent(renderer);
        Mix_PlayChannel(-1, gWrong, 0);
        score -= point;
        applyImage(pic0Texture3, renderer, pics[4].getPos2().getX(), pics[4].getPos2().getY(), 175, 175);
        if(prevPos.getX() != 0 || prevPos.getY() != 0){
            applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
        }
        SDL_Delay(500);
        SDL_RenderPresent(renderer);
        prevPath = "";
        prevPos = {0,0};
        count = 0;
        applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
        SDL_RenderPresent(renderer);
        loadScore(score, renderer, gFont, gTexture);
    }
    if(!pics[5].getFind() && x > pics[5].getPos1().getX() && x < pics[5].getPos1().getX() + 175 && y > pics[5].getPos1().getY() && y < pics[5].getPos1().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic5Texture3, renderer, pics[5].getPos1().getX(), pics[5].getPos1().getY(), 175, 175);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[5].getPos1().getX() || prevPos.getY() != pics[5].getPos1().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[5].getPath();
                prevPos = pics[5].getPos1();
            }else{
                if(prevPath != pics[5].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[5].getFirstClick1()) score -= point;
                    applyImage(pic0Texture3, renderer, pics[5].getPos1().getX(), pics[5].getPos1().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[5].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[5].setFirstClick1(false);
    }
    if(!pics[5].getFind() && x > pics[5].getPos2().getX() && x < pics[5].getPos2().getX() + 175 && y > pics[5].getPos2().getY() && y < pics[5].getPos2().getY() + 175){
        Mix_PlayChannel(-1, gClick, 0);
        applyImage(pic5Texture3, renderer, pics[5].getPos2().getX(), pics[5].getPos2().getY(), 175, 175);
        SDL_RenderPresent(renderer);
        if(prevPos.getX() != pics[5].getPos2().getX() || prevPos.getY() != pics[5].getPos2().getY()){    
            if(count == 0){
                count = 1;
                prevPath = pics[5].getPath();
                prevPos = pics[5].getPos2();
            }else{
                if(prevPath != pics[5].getPath()){
                    Mix_PlayChannel(-1, gWrong, 0);
                    if(!pics[5].getFirstClick2()) score -= point;
                    applyImage(pic0Texture3, renderer, pics[5].getPos2().getX(), pics[5].getPos2().getY(), 175, 175);
                    if(prevPos.getX() != 0 || prevPos.getY() != 0){
                        applyImage(pic0Texture3, renderer, prevPos.getX(), prevPos.getY(), 175, 175);
                    }
                    SDL_Delay(500);
                    SDL_RenderPresent(renderer);
                }else{
                    Mix_PlayChannel(-1, gRight, 0);
                    pics[5].setFind(true);
                    score += point;
                }
                prevPath = "";
                prevPos = {0,0};
                count = 0;
                applyImage(scoreTexture3, renderer, 903, 257, 158, 203);
                SDL_RenderPresent(renderer);
                loadScore(score, renderer, gFont, gTexture);
            }
        }
        pics[5].setFirstClick2(false);
    }
}

void clean3(){
    SDL_DestroyTexture(pic0Texture3);
    SDL_DestroyTexture(pic1Texture3);
    SDL_DestroyTexture(pic2Texture3);
    SDL_DestroyTexture(pic3Texture3);
    SDL_DestroyTexture(pic4Texture3);
    SDL_DestroyTexture(pic5Texture3);
    SDL_DestroyTexture(xTexture3);
    SDL_DestroyTexture(scoreTexture3);
}
