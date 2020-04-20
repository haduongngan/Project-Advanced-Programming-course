//
// Created by Duong Ngan Ha on 13/04/2020.
//



#ifndef GAME_BRICK_H
#define GAME_BRICK_H

#include "LTexture.h"
#include <vector>
using namespace std;

class brick {
public:
    //brick-01
    LTexture obj;

    //brick-02
    LTexture brick02;

    //top left position
    SDL_Point mPosition;

    //brick dimensions
    double mWidth;
    double mHeight;

    //render?
    bool ren;

    //pile
    int pile;
    bool truepile;

    //Colum
    int col;

    //ham tao
    brick();

    //ham huy
    ~brick();

    //xac dinh xem co thuoc hang dang chon khong
    void setTruepile(int p);

    //xac dinh thuoc hang nao
    void setPile(int p);

    //xac dinh thuoc cot nao
    void setCol(int id);

    //render
    void rend();

    //xac dinh toa do brick
    void setPosition(int x, int y);

    //xu ly khi bam vao
    void handleEvent(SDL_Event* e, bool isrend[6][13], vector<int> &matrix);

};


#endif //GAME_BRICK_H
