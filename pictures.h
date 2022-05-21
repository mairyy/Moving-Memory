#ifndef PICTURES_H
#define PICTURES_H

#include <iostream>
#include <string>
#include "common.h"

using namespace std;

class Point{
    int x, y;
public:
    Point(){};
    Point(int x_, int y_): x(x_), y (y_){}
    ~Point(){};
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
    int frequency;
    bool find, firstClick1, firstClick2;
public:
    Picture();
    string getPath();
    void setPath(string path);
    Point getPos1();
    Point getPos2();
    void setPos1(int x, int y);
    void setPos2(int x, int y);
    int getFre();
    void setFre(int frequency);
    bool getFind();
    void setFind(bool find);
    bool getFirstClick1();
    void setFirstClick1(bool firstClick1);
    bool getFirstClick2();
    void setFirstClick2(bool firstClick2);
};

#endif