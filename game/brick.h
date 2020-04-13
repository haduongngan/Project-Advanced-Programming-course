//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
#include "LTexture.h"
using namespace std;

#ifndef GAME_BRICK_H
#define GAME_BRICK_H





class brick {
private:
    LTexture obj;

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

public:
    brick();
    ~brick();
    bool getRen();
    void setRen(bool c);
    void setTruepile(int p);
    void setPile(int p);
    int getX();
    int getY();
    int getPile();
    void rend();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
};


#endif //GAME_BRICK_H
