#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>
#include <string>
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "game.h"
#include "VARIABLES_PROTOTYPE.h"
#include "level.h"
#include "welcome.h"
#include "LTexture.h"
using namespace std;

const double SCREEN_WIDTH = 532.992;
const double SCREEN_HEIGHT = 666.24;

//the window
SDL_Window* window = nullptr;

//surface
SDL_Surface* screenSurface = nullptr;

//the image
SDL_Surface* image = nullptr;

//the window renderer
SDL_Renderer* renderer = nullptr;

//current displayed texture
SDL_Texture* Texture = nullptr;

//globally used font
TTF_Font* font = nullptr;

//rendered texture
LTexture texttexture;

//path
char* path = "";

LTexture brick;
LTexture Backgr;
LTexture active;
LTexture unactive;






int main(int argc, char** argv) {
    if ( !init() ){
        cout << "Failed to initialize!\n";
    }
    else {

       // welcometogame();
        loadLevel2();
        //loadLevel4();
        close();
    }

    return 0;
}
