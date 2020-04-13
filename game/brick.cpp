//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include "brick.h"

brick :: brick(){
    if (!obj.loadFFile("../image/brick-01.png")){
        cout << "Failed to load brick" << endl;
    }
    else {
        mWidth = obj.getWidth();
        mHeight = obj.getHeight();
        mPosition.x = 0;
        mPosition.y = 0;
        ren = true;
        pile = 0;
        truepile = false;
    }
}

brick :: ~brick(){
    obj.free();
}

bool brick :: getRen(){
    return ren;
}

void brick :: setRen(bool c){
    ren = c;
}

int brick :: getX(){
    return mPosition.x;
}

int brick :: getY(){
    return mPosition.y;
}

void brick :: rend(){
    if (ren){
        obj.render(mPosition.x, mPosition.y);
    }
}

void brick :: setPile (int p){
    pile = p;
}

void brick :: setTruepile(int pileNow) {
    if (pile == pileNow) truepile = true;
    else truepile = false;
}

int brick :: getPile(){
    return pile;
}

void brick :: setPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

void brick :: handleEvent(SDL_Event* e){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button
        bool inside = true;
        if (x < mPosition.x) inside = false;
        else if (x > mPosition.x + mWidth) inside = false;
        else if (y < mPosition.y) inside = false;
        else if (y > mPosition.y + mHeight) inside = false;

        if (inside && truepile) ren = false;
        else ren = true;
    }
}