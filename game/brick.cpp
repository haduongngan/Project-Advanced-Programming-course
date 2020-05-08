//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include "brick.h"

//constructor : 8 - 23
brick :: brick(){
    if (!(obj.loadFFile("../image/brick-01.png") && brick02.loadFFile("../image/brick02.png"))){
        cout << "Failed to load brick" << endl;
    }
    else {
        mWidth = obj.mWidth;
        mHeight = obj.mHeight;
        mPosition.x = 0;
        mPosition.y = 0;
        ren = true;
        ren02 = false;
        pile = 0;
        col = 0;
        truepile = false;
    }
}

//destructor : 26 - 29
brick :: ~brick(){
    obj.free();
    brick02.free();
}


/* set "truepile" based on the pile could be selected in this turn
 * take the id of pile could be selected in this turn as the parameter
 */
void brick :: setTruepile(int pileNow) {
    truepile = (pile == pileNow);
}

/* determine the own brick's pile
 * take the id of this brick's pile as the parameter
 */
void brick :: setPile (int p){
    pile = p;
}

/* determine the own brick's column
 * take the id of this brick's column as the parameter
 */
void brick :: setCol(int id){
    col = id;
}

//render
void brick :: rend() const{
    obj.render(mPosition.x, mPosition.y);
}

//determine the own brick's Position
void brick :: setPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

/* handle when mouse event happened
 * the 1st parameter is main pointer SDL_Event.
 * The 2nd is the vector which determine if bricks should be render or not,
 * and the last parameter is the vector saving number of bricks each pile
 */
void brick :: handleEvent(SDL_Event* e, vector<vector<bool>> &isrend, vector<int> &matrix){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION ){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is in brick
        bool inside = true;
        if (x < mPosition.x) inside = false;
        else if (x > mPosition.x + mWidth) inside = false;
        else if (y < mPosition.y) inside = false;
        else if (y > mPosition.y + mHeight) inside = false;

        //bricks must be selected from right to left
        if (inside && truepile && e->type == SDL_MOUSEBUTTONUP && !isrend[pile - 1][col] && isrend[pile - 1][col - 1]) {
            ren = false;
            matrix[pile-1]--;
            isrend[pile-1][col-1] = false;
            Mix_PlayChannel(-1, selectBrick, 0);
        }
        else ren = true;

        if (inside && e->type == SDL_MOUSEMOTION && isrend[pile-1][col-1]){
            ren02  = true;
        }
        else {
            ren02 = false;
        }
    }

}