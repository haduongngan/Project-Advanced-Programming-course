//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include "brick.h"

//ham tao
brick :: brick(){
    if (!(obj.loadFFile("../image/brick-01.png") && brick02.loadFFile("../image/brick02.png"))){
        cout << "Failed to load brick" << endl;
    }
    else {
        mWidth = obj.getWidth();
        mHeight = obj.getHeight();
        mPosition.x = 0;
        mPosition.y = 0;
        ren = true;
        pile = 0;
        col = 0;
        truepile = false;
    }
}

//ham huy
brick :: ~brick(){
    obj.free();
    brick02.free();
}

//lay gtri ren
bool brick :: getRen(){
    return ren;
}

//lay toa do X
int brick :: getX(){
    return mPosition.x;
}

//lay toa do Y
int brick :: getY(){
    return mPosition.y;
}

//lay so hang no dang o
int brick :: getPile(){
    return pile;
}

//lay so cot no dang o
int brick :: getCol(){
    return col;
}

//xac dinh xem co thuoc hang dang chon khong
void brick :: setTruepile(int pileNow) {
    if (pile == pileNow) truepile = true;
    else truepile = false;
}

//xac dinh thuoc hang nao
void brick :: setPile (int p){
    pile = p;
}

//xac dinh thuoc cot nao
void brick :: setCol(int id){
    col = id;
}

//render
void brick :: rend(){
    //if (ren){
        obj.render(mPosition.x, mPosition.y);
    //}
}

//xac dinh toa do brick
void brick :: setPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

//xu ly khi bam vao
void brick :: handleEvent(SDL_Event* e, bool isrend[6][13]){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION ){ //|| e->type == SDL_MOUSEBUTTONUP e->type == SDL_MOUSEBUTTONDOWN
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button
        bool inside = true;
        if (x < mPosition.x) inside = false;
        else if (x > mPosition.x + mWidth) inside = false;
        else if (y < mPosition.y) inside = false;
        else if (y > mPosition.y + mHeight) inside = false;

        if (inside && truepile && e->type == SDL_MOUSEBUTTONUP && isrend[pile-1][col] == false) ren = false;
        else if (inside && e->type == SDL_MOUSEMOTION && isrend[pile-1][col-1] == true){
            brick02.render(mPosition.x, mPosition.y-3 );
        }
        else ren = true;
    }

}