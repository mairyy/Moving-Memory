#include "pictures.h"

Picture::Picture(){
    path = "";
    pos1 = {0, 0};
    pos2 = {0, 0};
    frequency = 0;
    find = false;
}

string Picture::getPath(){
    return path;
}

void Picture::setPath(string path){
    this->path = path;
}

Point Picture::getPos1(){
    return pos1;
}

Point Picture::getPos2(){
    return pos2;
}

void Picture::setPos1(int x, int y){
    pos1.setX(x);
    pos1.setY(y);
}

void Picture::setPos2(int x, int y){
    pos2.setX(x);
    pos2.setY(y);
}

int Picture::getFre(){
    return frequency;
}

void Picture::setFre(int frequency){
    this->frequency = frequency;
}

bool Picture::getFind(){
    return find;
}

void Picture::setFind(bool find){
    this->find = find;
}