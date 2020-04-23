//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include "LTexture.h"
#include "VARIABLES_PROTOTYPE.h"


//khoi tao
LTexture :: LTexture(){
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

//ham huy
LTexture :: ~LTexture(){
    free();
}

//load image -> mTexture
bool LTexture :: loadFFile(char* path){
    free();

    //the final texture
    SDL_Texture* newTexture = nullptr;


    //Load image
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr){
        cout << "Failed to load image " << path << ". SDL_image Error: " << IMG_GetError();
    }
    else {
        //color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 0xFF, 0xFF));

        //create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr){
            cout << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << endl;
        }
        else {
            //get image dimesions
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    //return
    mTexture = newTexture;
    return (mTexture != nullptr);
}

//create image from font string -> mTexture
bool LTexture :: loadFromRenderedText(char* texturetext, SDL_Colour textColor){
    free();

    //render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, texturetext, textColor);
    if (textSurface == nullptr){
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == nullptr){
            cout << "Unable to create textture from rendered text! SDL Error: " << SDL_GetError() << endl;
        }
        else {
            mWidth = textSurface -> w;
            mHeight = textSurface -> h;
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture != nullptr;

}

//deallocates texture
void LTexture :: free(){
    if (mTexture != nullptr){
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

//renders texture at given point
void LTexture :: render(int x, int y){
    //set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, static_cast<int>(mWidth), static_cast<int>(mHeight)};
    SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
}

//get image dimensions
double LTexture :: getWidth(){
    return mWidth;
}
double LTexture :: getHeight(){
    return mHeight;
}