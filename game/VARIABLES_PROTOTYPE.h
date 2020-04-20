//
// Created by Duong Ngan Ha on 12/04/2020.
//



#ifndef GAME_VARIABLES_PROTOTYPE_H
#define GAME_VARIABLES_PROTOTYPE_H

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
#include "game.h"

using namespace std;
extern  char* pathfont;
extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;
extern vector<vector<int>>data;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* Texture;
extern TTF_Font* font;
extern LTexture texttexture;

extern LTexture background[7]; //0: nen tron, 1 la nen winner, 2-6: nen theo so pile
extern LTexture brick;
extern LTexture brick_02;
extern LTexture active;
extern LTexture unactive;
extern LTexture hint;
extern LTexture menu;
extern LTexture nextnode;
extern LTexture minusnode;
extern LTexture plusnode;
extern LTexture text_input;


bool init();

SDL_Texture* loadTexture(char* pathImage);

bool loadImage(char* pathImage);

bool loadText(char* pathFont, char* text, int size);

void close();

vector<int> chooseLevel(const char* f, int level, vector<vector<int>>data);

void loadData(const char* f);

void welcome(class Game &yourGame);

void help(class Game &yourGame);

void setup(class Game &yourGame);

void level(class Game &yourGame);

void handleEventCase1(SDL_Event* e, bool &quit, int &WinCase);

void handleEventCase2(SDL_Event* e, int &WinCase);

void handleEventCase3(SDL_Event* e, int &WinCase, class Game &yourGame);

void handleEventCase4(SDL_Event* e, int &WinCase, class Game &yourGame);

void handleEventCase5(SDL_Event* e, int &WinCase, class Game &yourGame, bool &quit);

#endif //GAME_VARIABLES_PROTOTYPE_H
