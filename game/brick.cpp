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
        ren02 = false;
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
void brick :: handleEvent(SDL_Event* e, vector<vector<bool>> &isrend, vector<int> &matrix){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION ){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button
        bool inside = true;
        if (x < mPosition.x) inside = false;
        else if (x > mPosition.x + mWidth) inside = false;
        else if (y < mPosition.y) inside = false;
        else if (y > mPosition.y + mHeight) inside = false;

        if (inside && truepile && e->type == SDL_MOUSEBUTTONUP && isrend[pile-1][col] == false && isrend[pile-1][col-1] == true) {
            ren = false;
            matrix[pile-1]--;
            isrend[pile-1][col-1] = false;
            //cout << pile << " " <<col << " " << isrend[pile-1][col-1] << endl;
        }
        else ren = true;

        if ((inside && e->type == SDL_MOUSEMOTION && isrend[pile-1][col-1] == true) // ||
        //(inside && e->type == SDL_MOUSEBUTTONUP && isrend[pile-1][col-1] == true && !truepile) ||
                //(inside && e->type == SDL_MOUSEBUTTONUP && isrend[pile-1][col-1] == true && isrend[pile-1][col])
                ){
            //brick02.render(mPosition.x, mPosition.y-3 );
            ren02  = true;
        }
        else {
            ren02 = false;
        }
    }

}