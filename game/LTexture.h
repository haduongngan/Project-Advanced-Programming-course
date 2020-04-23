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

class LTexture {
private:
    SDL_Texture* mTexture;

    //image dimensions
    double mWidth;
    double mHeight;

public:
    //ham tao
    LTexture();

    //ham huy
    ~LTexture();

    //load image -> mTexture
    bool loadFFile(char* path);

    //create image from font string -> mTexture
    bool loadFromRenderedText (char* texturetext, SDL_Colour textColor);

    //deallocates texture
    void free();

    //renders texture at given point
    void render(int x, int y);

    //get image dimensions
    double getWidth();
    double getHeight();

};


#endif //GAME_LTEXTURE_H