//
// Created by Duong Ngan Ha on 13/04/2020.
//


#ifndef GAME_BRICK_H
#define GAME_BRICK_H

#include "LTexture.h"
#include <vector>
using namespace std;
//sound effect
extern Mix_Chunk *selectBrick;

struct brick {
    //brick-01
    LTexture obj;

    //brick-02 - the bigger brick
    LTexture brick02;

    //top left position
    SDL_Point mPosition;

    //brick dimensions
    double mWidth;
    double mHeight;

    //render?
    bool ren; //normal brick
    bool ren02; //bigger brick

    //pile
    int pile;
    bool truepile;

    //Colum
    int col;

    brick();

    ~brick();


    /* set "truepile" based on the pile could be selected in this turn
    * take the id of pile could be selected in this turn as the parameter
    */
    void setTruepile(int p);

    /* determine the own brick's pile
    * take the id of this brick's pile as the parameter
    */
    void setPile(int p);

    /* determine the own brick's column
    * take the id of this brick's column as the parameter
    */
    void setCol(int id);

    //render
    void rend() const;

    //determine the own brick's Position
    void setPosition(int x, int y);

    /* handle when mouse event happened
    * the 1st parameter is main pointer SDL_Event.
    * The 2nd is the vector which determine if bricks should be render or not,
    * and the last parameter is the vector saving number of bricks each pile
    */
    void handleEvent(SDL_Event* e, vector<vector<bool>> &isrend, vector<int> &matrix);

};


#endif //GAME_BRICK_H