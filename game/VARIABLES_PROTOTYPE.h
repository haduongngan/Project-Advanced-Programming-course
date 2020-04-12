//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#ifndef GAME_VARIABLES_PROTOTYPE_H
#define GAME_VARIABLES_PROTOTYPE_H

extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Surface* image;

bool init();
bool loadMedia(char* path);
SDL_Surface* loadSurface(char* path);
void close();
void eloop();

#endif //GAME_VARIABLES_PROTOTYPE_H
