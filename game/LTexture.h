//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

#ifndef GAME_LTEXTURE_H
#define GAME_LTEXTURE_H

extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Surface* image;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

class LTexture {
private:
    SDL_Texture* mTexture;

    //image dimensions
    double mWidth;
    double mHeight;

public:
    LTexture();
    ~LTexture();

    //load image
    bool loadFFile(char* path);

    //deallocates texture
    void free();

    //renders texture at given point
    void render(int x, int y);
    //void render(int x, int y, SDL_Rect* clip = nullptr);

    //get image dimensions
    double getWidth();
    double getHeight();

    //create image from font string
    bool loadFromRenderedText (char* texturetext, SDL_Colour textColor);

    //set color modulation
    //void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //set blending
    //void setBlendMode(SDL_BlendMode blending);
};


#endif //GAME_LTEXTURE_H
