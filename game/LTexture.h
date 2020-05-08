//
// Created by Duong Ngan Ha on 13/04/2020.
//



#ifndef GAME_LTEXTURE_H
#define GAME_LTEXTURE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

extern SDL_Renderer* renderer;
extern TTF_Font* font;

struct LTexture {
    SDL_Texture* mTexture;

    //image dimensions
    double mWidth;
    double mHeight;

    //constructor
    LTexture();

    //destructor
    ~LTexture();

    /*load image -> mTexture
     * take path to image as the parameter
     */
    bool loadFFile(char* path);

    /* create image from font string -> mTexture
    * the 1st parameter is content of text, the 2nd parameter is color of text
    */
    bool loadFromRenderedText (char* texturetext, SDL_Colour textColor);

    //deallocates texture
    void free();

    //renders texture at given point
    void render(int x, int y) const;


};


#endif //GAME_LTEXTURE_H