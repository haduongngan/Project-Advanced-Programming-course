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
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#ifndef GAME_VARIABLES_PROTOTYPE_H
#define GAME_VARIABLES_PROTOTYPE_H

extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;
extern vector<vector<int>>data;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* Texture;
extern LTexture brick;
extern LTexture Backgr;
extern LTexture active;
extern LTexture unactive;
extern LTexture Node;
extern LTexture texttexture;


bool init();

SDL_Texture* loadTexture(char* pathImage);

bool loadImage(char* pathImage);

bool loadText(char* pathFont, char* text, int size);

void close();

vector<int> chooseLevel(const char* f, int level, vector<vector<int>>data);

void loadData(const char* f);




#endif //GAME_VARIABLES_PROTOTYPE_H
