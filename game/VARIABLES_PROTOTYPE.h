//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include <cmath>
#include <string>
#include <cstring>
using namespace std;

#ifndef GAME_VARIABLES_PROTOTYPE_H
#define GAME_VARIABLES_PROTOTYPE_H

extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Renderer* renderer;
extern SDL_Texture* Texture;
extern LTexture brick;
extern LTexture Backgr;
extern LTexture active;
extern LTexture texttexture;

bool init();
bool loadMedia(char* path);
SDL_Surface* loadSurface(char* path);
SDL_Texture* loadTexture(char* path);
bool loadImage(char* path);
bool loadText(char* path, char* text);
void eloop();
void close();
#endif //GAME_VARIABLES_PROTOTYPE_H
