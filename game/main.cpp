#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "game.h"
using namespace std;



//SDL

//Screen dimension const
const double SCREEN_WIDTH = 532.992;
const double SCREEN_HEIGHT = 666.24;

//the window
SDL_Window* window = nullptr;

//surface
SDL_Surface* screenSurface = nullptr;

//the image
SDL_Surface* image = nullptr;

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
            //get window surface
            screenSurface = SDL_GetWindowSurface(window);

        }
    }
    return success;
}

//Load media
bool loadMedia(){
    bool success = true;

    //load image
    //image = IMG_Load("../color-01.png");
    image = IMG_Load("../image/background4.png");
    //image = SDL_LoadBMP("../backgr.bmp");
    if (image == nullptr){
        cout << "Unable to load image! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    return success;
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

int main(int argc, char** argv) {

    //Initialize SDL
    if ( !init() ){
        cout << "Failed to initialize!\n";
    }
    else {
        //load media
        if ( !loadMedia() ){
            cout << "Failed to load media!\n ";
        }
        else {
            //apply the image
            SDL_BlitSurface(image, nullptr, screenSurface, nullptr);
            //Update
            SDL_UpdateWindowSurface(window);

            eloop();
        }
    }
    //free resourses and close
    close();
    return 0;
}
