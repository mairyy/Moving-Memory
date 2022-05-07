#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

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

class Point{
    int x, y;
public:
    Point(){};
    Point(int x_, int y_): x(x_), y (y_){}
    int getX(){return x;}
    int getY(){return y;}
    void setX(int x){this->x = x;}
    void setY(int y){this->y = y;}
    void print(){
        cout << "(" << x << "," << y << ")\n";
    }
};

class Picture{
    string path;
    Point pos1, pos2;
    int frequency, count;
public:
    Picture(){
        path = "";
        pos1 = {0, 0};
        pos2 = {0, 0};
        frequency = 0;
        count = 0;
    }
    string getPath(){return path;}
    void setPath(string path){this->path = path;}
    Point getPos1(){return pos1;}
    Point getPos2(){return pos2;}
    void setPos1(int x, int y){
        pos1.setX(x);
        pos1.setY(y);
    }
    void setPos2(int x, int y){
        pos2.setX(x);
        pos2.setY(y);
    }
    int getFre(){return frequency;}
    void setFre(int frequency){this->frequency = frequency;}
    int getCount(){return count;}
    void setCount(int count){this->count = count;}
};

bool init();
SDL_Surface* loadImageFromFile(string path);
SDL_Surface* deleteBackGroundImage(SDL_Surface* image, Uint8 red, Uint8 green, Uint8 blue);
SDL_Texture* loadImageFromRenderedText(string textureText, SDL_Color textColor);
void applyImage(SDL_Texture* texture, int x, int y, int w, int h);
void loadText(string text, string textFont, int fontSize, Uint8 red, Uint8 green, Uint8 blue);
void applyText(string text, int x, int y);
void clean();

int main(int argc, char* args[]){
    int x, y;
    bool quit = false;
    if(!init()){
        cout << "Failed to initialize!\n";
    }else{
        SDL_Surface* backGround = loadImageFromFile("Pictures/gameBackGround.png");
        SDL_Texture* backGroundTexture = SDL_CreateTextureFromSurface(gRenderer, backGround);
        applyImage(backGroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        const int totalPos = 6;
        Point posArr[totalPos] = {{110, 115}, {360, 115}, {610, 115}, {110, 365}, {360, 365}, {610, 365}};
        SDL_Surface* pic0 = loadImageFromFile("Pictures/0.png");
        SDL_Texture* pic0Texture = SDL_CreateTextureFromSurface(gRenderer, pic0);
        for(int i = 0; i < totalPos; i++){
            applyImage(pic0Texture, posArr[i].getX(), posArr[i].getY(), 190, 190);
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
        SDL_Surface* pic1 = loadImageFromFile(pics[0].getPath());
        SDL_Texture* pic1Texture = SDL_CreateTextureFromSurface(gRenderer, pic1);
        SDL_Surface* pic2 = loadImageFromFile(pics[1].getPath());
        SDL_Texture* pic2Texture = SDL_CreateTextureFromSurface(gRenderer, pic2);
        SDL_Surface* pic3 = loadImageFromFile(pics[2].getPath());
        SDL_Texture* pic3Texture = SDL_CreateTextureFromSurface(gRenderer, pic3);
        string prevPath = "";
        Point prevPos;
        int count = 0;
        while(!quit){
            SDL_GetMouseState(&x, &y);
            while(SDL_PollEvent(&gEvent) != 0){
                if(gEvent.type == SDL_QUIT){
                    quit = true;
                }
                if(gEvent.type == SDL_MOUSEBUTTONDOWN){
                    if(x > pics[0].getPos1().getX() && x < pics[0].getPos1().getX() + 190 && y > pics[0].getPos1().getY() && y < pics[0].getPos1().getY() + 190){
                        applyImage(pic1Texture, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(count == 0){
                            count = 1;
                            prevPath = pics[0].getPath();
                            prevPos = pics[0].getPos1();
                        }else{
                            if(prevPath != pics[0].getPath()){
                                applyImage(pic0Texture, pics[0].getPos1().getX(), pics[0].getPos1().getY(), 190, 190);
                                applyImage(pic0Texture, prevPos.getX(), prevPos.getY(), 190, 190);
                                SDL_Delay(500);
                                SDL_RenderPresent(gRenderer);
                            }
                            prevPath = "";
                            prevPos = {0,0};
                            count = 0;
                        }
                    }
                    if(x > pics[0].getPos2().getX() && x < pics[0].getPos2().getX() + 190 && y > pics[0].getPos2().getY() && y < pics[0].getPos2().getY() + 190){
                        applyImage(pic1Texture, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(count == 0){
                            count = 1;
                            prevPath = pics[0].getPath();
                            prevPos = pics[0].getPos2();
                        }else{
                            if(prevPath != pics[0].getPath()){
                                applyImage(pic0Texture, pics[0].getPos2().getX(), pics[0].getPos2().getY(), 190, 190);
                                applyImage(pic0Texture, prevPos.getX(), prevPos.getY(), 190, 190);
                                SDL_Delay(500);
                                SDL_RenderPresent(gRenderer);
                            }
                            prevPath = "";
                            prevPos = {0,0};
                            count = 0;
                        }
                    }
                    if(x > pics[1].getPos1().getX() && x < pics[1].getPos1().getX() + 190 && y > pics[1].getPos1().getY() && y < pics[1].getPos1().getY() + 190){
                        applyImage(pic2Texture, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(count == 0){
                            count = 1;
                            prevPath = pics[1].getPath();
                            prevPos = pics[1].getPos1();
                        }else{
                            if(prevPath != pics[1].getPath()){
                                applyImage(pic0Texture, pics[1].getPos1().getX(), pics[1].getPos1().getY(), 190, 190);
                                applyImage(pic0Texture, prevPos.getX(), prevPos.getY(), 190, 190);
                                SDL_Delay(500);
                                SDL_RenderPresent(gRenderer);
                            }
                            prevPath = "";
                            prevPos = {0,0};
                            count = 0;
                        }
                    }
                    if(x >  pics[1].getPos2().getX() && x < pics[1].getPos2().getX() + 190 && y > pics[1].getPos2().getY() && y < pics[1].getPos2().getY() + 190){
                        applyImage(pic2Texture, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(count == 0){
                            count = 1;
                            prevPath = pics[1].getPath();
                            prevPos = pics[1].getPos2();
                        }else{
                            if(prevPath != pics[1].getPath()){
                                applyImage(pic0Texture, pics[1].getPos2().getX(), pics[1].getPos2().getY(), 190, 190);
                                applyImage(pic0Texture, prevPos.getX(), prevPos.getY(), 190, 190);
                                SDL_Delay(500);
                                SDL_RenderPresent(gRenderer);
                            }
                            prevPath = "";
                            prevPos = {0,0};
                            count = 0;
                        }
                    }
                    if(x > pics[2].getPos1().getX() && x < pics[2].getPos1().getX() + 190 && y > pics[2].getPos1().getY() && y < pics[2].getPos1().getY() + 190){
                        applyImage(pic3Texture, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
                            SDL_RenderPresent(gRenderer);
                        if(count == 0){
                            count = 1;
                            prevPath = pics[2].getPath();
                            prevPos = pics[2].getPos1();
                        }else{
                            if(prevPath != pics[2].getPath()){
                                applyImage(pic0Texture, pics[2].getPos1().getX(), pics[2].getPos1().getY(), 190, 190);
                                applyImage(pic0Texture, prevPos.getX(), prevPos.getY(), 190, 190);
                                SDL_Delay(500);
                                SDL_RenderPresent(gRenderer);
                            }
                            prevPath = "";
                            prevPos = {0,0};
                            count = 0;
                        }
                    }
                    if(x > pics[2].getPos2().getX() && x < pics[2].getPos2().getX() + 190 && y > pics[2].getPos2().getY() && y < pics[2].getPos2().getY() + 190){
                        applyImage(pic3Texture, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
                        SDL_RenderPresent(gRenderer);
                        if(count == 0){
                            count = 1;
                            prevPath = pics[2].getPath();
                            prevPos = pics[2].getPos2();
                        }else{
                            if(prevPath != pics[2].getPath()){
                                applyImage(pic0Texture, pics[2].getPos2().getX(), pics[2].getPos2().getY(), 190, 190);
                                applyImage(pic0Texture, prevPos.getX(), prevPos.getY(), 190, 190);
                                SDL_Delay(500);
                                SDL_RenderPresent(gRenderer);
                            }
                            prevPath = "";
                            prevPos = {0,0};
                            count = 0;
                        }
                    }
                }
            }
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