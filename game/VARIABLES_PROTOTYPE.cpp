//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "VARIABLES_PROTOTYPE.h"
//starts up SDL and creates window


bool init(){
    bool success = true;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        success = false;
    }
    else {
        //Create window
        window = SDL_CreateWindow("NIM GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if ( window == nullptr ){
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
        else {
            //initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags)&imgFlags)) {
                cout << "SDL_image could not initialize!  SDL_image Error: " << IMG_GetError() << endl;
                success = false;
            }
            else {
                //get window surface
                screenSurface = SDL_GetWindowSurface(window);
            }
        }
    }
    return success;
}

//Load media
bool loadMedia(char* path){
    bool success = true;

    image = IMG_Load(path);
    if (image == nullptr){
        cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << endl;
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface(char* path){
    SDL_Surface* optimized = nullptr;
    if (!loadMedia(path)){
        cout << "Failed to load media!\n ";
    }
    else {
        optimized = SDL_ConvertSurface(image, screenSurface ->format,0);
        if (optimized == nullptr){
            cout << " Unable to optimize image! SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(image);
        image = nullptr;
    }
    return optimized;
}

//Frees media and shuts down SDl
void close(){
    SDL_FreeSurface(image);
    image = nullptr;

    SDL_DestroyWindow(window); //se take care screensurface
    window = nullptr;

    SDL_Quit();
}

void eloop(){
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
    }
}