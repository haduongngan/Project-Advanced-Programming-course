//
// Created by Duong Ngan Ha on 13/04/2020.
//

#include "LTexture.h"
#include "VARIABLES_PROTOTYPE.h"

LTexture :: LTexture(){
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}
LTexture :: ~LTexture(){
    free();
}

//load image
bool LTexture :: loadFFile(char* path){
    free();
    //the final texture
    SDL_Texture* newTexture = nullptr;

    //Load image
    if (!loadMedia(path)){
        cout << "Failed to load media!\n ";
    }
    else {
        //color key image
        SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image -> format, 0, 0xFF, 0xFF));

        //create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, image);
        if (newTexture == nullptr){
            cout << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << endl;
        }
        else {
            //get image dimesions
            mWidth = image -> w;
            mHeight = image -> h;
        }
        //SDL_FreeSurface(image);
    }
    //return
    mTexture = newTexture;
    return (mTexture != nullptr);
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