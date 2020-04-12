#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "game.h"
#include "VARIABLES_PROTOTYPE.h"
#include "level.h"
#include "welcome.h"
using namespace std;

const double SCREEN_WIDTH = 532.992;
const double SCREEN_HEIGHT = 666.24;

//the window
SDL_Window* window = nullptr;

//surface
SDL_Surface* screenSurface = nullptr;

//the image
SDL_Surface* image = nullptr;

//path
char* path = "";


int main(int argc, char** argv) {

    welcometogame();
    loadLevel1();

    return 0;
}
