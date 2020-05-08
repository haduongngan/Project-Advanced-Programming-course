//
// Created by Duong Ngan Ha on 12/04/2020.
//

#ifndef GAME_VARIABLES_PROTOTYPE_H
#define GAME_VARIABLES_PROTOTYPE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cmath>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include "game.h"
#include "LTexture.h"

using namespace std;

//path
extern char* pathfont;

//window size
extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;

// max pile (fixed) and max bricks in each pile
extern const int MAX_PILE;
extern const int MAX_BRICK;

//text color
extern const SDL_Color textColor_white;
extern const SDL_Color textColor_red;

//data
extern vector<vector<int>>data;

//SDl
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern LTexture texttexture;

extern LTexture background[7]; //0: basic backgr, 1: backgr winner, 2-6: backgr based on number of piles

//active status
extern LTexture active;
extern LTexture unactive;

//function nodes
extern LTexture hint;
extern LTexture menu;
extern LTexture nextnode;
extern LTexture minusnode;
extern LTexture plusnode;
extern LTexture text_input;

//music and sound effect
extern Mix_Music *gMusic;
extern Mix_Chunk *selectBrick;
extern Mix_Chunk *selectNode;
extern Mix_Chunk *win;
extern Mix_Chunk *switchTurn;

/*
 * initialize function : windown, renderer, IMG, TTF, mixer
 * return false if could not initialize
 */
bool init();

/*
 * load Music + sound effect
 * return false if could not load
 */
bool loadMusic();

/*
 * load Text -> texttexture
 * The 1st parameter is the path to font style.
 * The 2nd parameter is the content that we want to load.
 * The 3rd parameter is the size of text.
 * And the last parameter is the color.
 * (use function "loadFromRenderedText" of struct LTexture)
 */
bool loadText(char* pathFont, char* text, int size, const SDL_Color &textColor);

/*
 * close function: frees media and shus down SDL
 */
void close();

/*
 * take pathData (Stones.txt) as parameter
 * output: update vector Data
 */
void loadData(const char* f);

/*
 * Case 1 : Welcome to Nim game
 * A Game is sent into the method as a parameter
 * output: render backgr, nodes,... of case 1
 * use function loadText to load and member function render of LTexture to render.
 * if mouse position is in "text node", this text will be rendered in red color.
 */
void welcome(const struct Game &yourGame);

/*
 * Case 2 : Instructions
 * Take a Game as a parameter
 * output: render backgr, nodes,... of case 2
 * use function loadText to load and member function render of LTexture to render.
 */
void help(const struct Game &yourGame);

/*
 * Case 3 : Set up your game
 * take a Game as a parameter
 * output: render backgr, nodes,... of case 3
 * use function loadText to load and member function render of LTexture to render.
 */
void setup(const struct Game &yourGame);

/*
 * Case 4 : main screen based on level
 * take a Game as a parameter
 * output: render backgr, function nodes, bricks, name of players,... based on fixed parameter of the game
 * use function loadText to load and member function render of LTexture to render.
 */
void level(const struct Game &yourGame);

/*
 * Case 5: announce the winner
 * take a Game as a parameter
 * output: render backgr, congratulation, text nodes... based on fixed parameter of the game
 * use function loadText to load and member function render of LTexture to render.
 */
void winner(const struct Game &yourGame);

/*
 * Case 1 : Welcome to Nim game -> handle when Wincase == 1
 * the 1st parameter is main pointer SDL_Event. the 2nd is WinCase and the last paremeter is quit (= true -> quit game)
 * output: change WinCase (go to read rules or start set up game or quit)
 */
void handleEventCase1(SDL_Event* e, int &WinCase, bool &quit);

/*
 * Case 2 : Instructions -> handle when Wincase == 2
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase.
 * output: change WinCase (read rules complete and come to set up game)
 */
void handleEventCase2(SDL_Event* e, int &WinCase);

/*
 * Case 3 : Set up your game -> handle when Wincase == 3
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase and the last parameter is a Game
 * output: update the Game and change WinCase (set up completed)
 * use member functions of game to update game
 */
void handleEventCase3(SDL_Event* e, int &WinCase, struct Game &yourGame);

/*
 * Case 4 : main screen based on level -> handle when Wincase == 4
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase and the last parameter is a Game
 * output: update the Game and change WinCase (if have a winner)
 * handle based on play mode of game
 */
void handleEventCase4(SDL_Event* e, int &WinCase, struct Game &yourGame);

/*
 * Case 5: announce the winner -> handle when Wincase == 5
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase. The 3rd parameter is a Game and the last paremeter is quit (= true -> quit game).
 * output: change WinCase (based on player) and reset game.
 */
void handleEventCase5(SDL_Event* e, int &WinCase, struct Game &yourGame, bool &quit);

#endif //GAME_VARIABLES_PROTOTYPE_H