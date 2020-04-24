//
// Created by Duong Ngan Ha on 12/04/2020.
//



#ifndef GAME_VARIABLES_PROTOTYPE_H
#define GAME_VARIABLES_PROTOTYPE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
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
extern LTexture active;
extern LTexture unactive;
extern LTexture hint;
extern LTexture menu;
extern LTexture nextnode;
extern LTexture minusnode;
extern LTexture plusnode;
extern LTexture text_input;

extern Mix_Music *gMusic;
extern Mix_Chunk *selectBrick;
extern Mix_Chunk *selectNode;
extern Mix_Chunk *win;
extern Mix_Chunk *switchTurn;

bool init();

bool loadMusic();

bool loadText(char* pathFont, char* text, int size);

bool loadTextNew(char* pathFont, char* text, int size);

void close();

vector<int> chooseLevel(int level, vector<vector<int>>data);

void loadData(const char* f);

void welcome(struct Game &yourGame);

void help(struct Game &yourGame);

void setup(struct Game &yourGame);

void level(struct Game &yourGame);

void handleEventCase1(SDL_Event* e, int &WinCase, bool &quit);

void handleEventCase2(SDL_Event* e, int &WinCase);

void handleEventCase3(SDL_Event* e, int &WinCase, struct Game &yourGame);

void handleEventCase4(SDL_Event* e, int &WinCase, struct Game &yourGame);

void handleEventCase5(SDL_Event* e, int &WinCase, struct Game &yourGame, bool &quit);

#endif //GAME_VARIABLES_PROTOTYPE_H