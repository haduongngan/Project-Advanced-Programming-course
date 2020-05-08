//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "VARIABLES_PROTOTYPE.h"

/* 11 - 58
 * initialize function : windown, renderer, IMG, TTF, mixer
 * return false if could not initialize
 */
bool init(){
    bool success = true;
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
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
            //create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr){
                cout << "Renderer could not be create! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else {
                //initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags)&imgFlags)) {
                    cout << "SDL_image could not initialize!  SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                //initialize SDL ttf
                if (TTF_Init() == -1){
                    cout << "SDL_ttf could not initialize!  SDL_ttf Error: " << TTF_GetError() << endl;
                    success = false;
                }

                //initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                    cout << "SDL_mixer could not initialize!  SDL_mixer Error: " << Mix_GetError() << endl;
                    success = false;
                }

            }
        }
    }
    return success;
}


/* 66 - 105
 * load Music + sound effect
 * return false if could not load
 */

bool loadMusic(){
    bool succcess = true;

    //load music
    gMusic = Mix_LoadMUS("../music/08-Frappe-Snowland_-Sherbet-Land-_1_-_mp3cut.net_.ogg");
    if (gMusic == nullptr){
        cout << "Failed to load Frappe music! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    //load sound effect;
    //when select a brick
    selectBrick = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_pick_up_collect_item_sci_fi_004_46204.ogg");
    if (selectBrick == nullptr){
        cout << "Failed to load selectBrick sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    //when select a node
    selectNode = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_musical_bright_ping_musical_short_positive_002_44884.ogg");
    if (selectNode == nullptr){
        cout << "Failed to load selectNode sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    //congratulate on the victory
    win = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_fanfare_synthesized_brass_44793.ogg");
    if (win == nullptr){
        cout << "Failed to load win sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    //when switch form a player to another
    switchTurn = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_bright_positive_002_44875.ogg");
    if (switchTurn == nullptr){
        cout << "Failed to load switchTurn sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }
    return succcess;
}


/* 116 - 133
 * load Text -> texttexture
 * The 1st parameter is the path to font style.
 * The 2nd parameter is the content that we want to load.
 * The 3rd parameter is the size of text.
 * And the last parameter is the color.
 * (use function "loadFromRenderedText" of struct LTexture)
 */
bool loadText(char* pathFont, char* text, int size, const SDL_Color &textColor){
    bool success = true;
    TTF_CloseFont(font);
    font = nullptr;
    //open the font with fixed path and size
    font = TTF_OpenFont(pathFont, size);
    if (font == nullptr){
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else {
        //render text with fixed content and color
        if (!texttexture.loadFromRenderedText(text, textColor)){
            cout << "Failed to render text texture\n";
            success = false;
        }
    }
    return success;
}


/* 141 - 184
 * close function: frees media and shus down SDL
 */

void close(){
    active.free();
    unactive.free();

    hint.free();
    nextnode.free();
    menu.free();

    minusnode.free();
    plusnode.free();
    text_input.free();

    for (int i = 0; i < 7; i++){
        background[i].free();
    }

    texttexture.free();

    Mix_FreeChunk(selectBrick);
    Mix_FreeChunk(selectNode);
    Mix_FreeChunk(win);
    Mix_FreeChunk(switchTurn);
    selectNode = nullptr;
    selectBrick = nullptr;
    win = nullptr;
    switchTurn = nullptr;

    Mix_FreeMusic(gMusic);
    gMusic = nullptr;

    TTF_CloseFont(font);
    font = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/* 190 - 202
 * take pathData (Stones.txt) as parameter
 * output: update vector Data
 */
void loadData(const char* f){
    ifstream infile(f);
    string line;
    while(getline(infile,line)){
        vector<int> tmp;
        int value;
        stringstream iss(line);
        while(iss >> value){
            tmp.push_back(value);
        }
        data.push_back(tmp);
    }
}

/* 211 - 281
 * Case 1 : Welcome to Nim game
 * A Game is sent into the method as a parameter
 * output: render backgr, nodes,... of case 1
 * use function loadText to load and member function render of LTexture to render.
 * if mouse position is in "text node", this text will be rendered in red color.
 */

void welcome(const struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    background[0].render(0,0);

    //get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //check if mourse is in node
    bool inhelp = true;
    bool instart = true;
    bool inquit = true;
    if (x < 199) inquit = false;
    else if (x > 199 + 100) inquit = false;
    else if (y < 440) inquit = false;
    else if (y > 440 + 40) inquit = false;

    if (x < 199) inhelp = false;
    else if (x > 199 + 111) inhelp = false;
    else if (y < 360) inhelp = false;
    else if (y > 360 + 60) inhelp = false;

    if (x < 199) instart = false;
    else if (x > 199 + 120) instart = false;
    else if (y < 300) instart = false;
    else if (y > 300 + 40) instart = false;

    if (loadText(pathfont, "Welcome to", 60, textColor_white)) {
        texttexture.render(90, 60);
    }
    if (loadText(pathfont, "NIM GAME", 70, textColor_red)) {
        texttexture.render(150, 130);
    }

    if (instart){
        if (loadText(pathfont, "Start", 52, textColor_red)) {
            texttexture.render(193, 270);
        }
    }
    else {
        if (loadText(pathfont, "Start", 52, textColor_white)) {
            texttexture.render(193, 270);
        }
    }
    if (inhelp){
        if (loadText(pathfont, "Help", 52, textColor_red)) {
            texttexture.render(199, 340);
        }
    }
    else {
        if (loadText(pathfont, "Help", 52, textColor_white)) {
            texttexture.render(199, 340);
        }
    }
    if (inquit){
        if (loadText(pathfont, "Quit", 52, textColor_red)) {
            texttexture.render(199, 410);
        }
    }
    else {
        if (loadText(pathfont, "Quit", 52, textColor_white)) {
            texttexture.render(199, 410);
        }
    }

    SDL_RenderPresent(renderer);

}


/* 292 - 369
 * Case 2 : Instructions
 * Take a Game as a parameter
 * output: render backgr, nodes,... of case 2
 * use function loadText to load and member function render of LTexture to render.
 */

void help(const struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    background[0].render(0,0);

    if (loadText(pathfont, "Instructions", 60, textColor_white)) {
        texttexture.render(90, 0);
    }

    if (loadText(pathfont, "Two players take turns removing bricks", 27, textColor_white)) {
        texttexture.render(30, 80);
    }
    if (loadText(pathfont, "from one of the rows that appear.", 27, textColor_white)) {
        texttexture.render(70, 105);
    }

    if (loadText(pathfont, "You must select at least one brick ", 27, textColor_white)) {
        texttexture.render(75, 139);
    }
    if (loadText(pathfont, "in your turn.", 27, textColor_white)) {
        texttexture.render(190, 164);
    }

    if (loadText(pathfont, "Click the NEXT button to", 27, textColor_white)) {
        texttexture.render(120, 198);
    }
    if (loadText(pathfont, "end your turn.", 27, textColor_white)) {
        texttexture.render(190, 223);
    }

    if (loadText(pathfont, "During the game, you can use", 27, textColor_white)) {
        texttexture.render(50, 257);
    }
    hint.render(400,257);
    if (loadText(pathfont, "(one time) to skip your turn.", 27, textColor_white)) {
        texttexture.render(65, 282);
    }

    if (loadText(pathfont, "The player removing the last", 27, textColor_white)) {
        texttexture.render(100, 316);
    }
    if (loadText(pathfont, "brick will win the game.", 27, textColor_white)) {
        texttexture.render(125, 341);
    }

    if (loadText(pathfont, "You can choose 1 of 3 play modes:", 27, textColor_white)) {
        texttexture.render(73, 375);
    }
    if (loadText(pathfont, "1. Player VS Player", 27, textColor_white)) {
        texttexture.render(150, 400);
    }
    if (loadText(pathfont, "2. Player VS AI", 27, textColor_white)) {
        texttexture.render(150, 425);
    }
    if (loadText(pathfont, "3. Player VS SmartAI", 27, textColor_white)) {
        texttexture.render(150, 450);
    }

    if (loadText(pathfont, "You are able choose who goes first.", 27, textColor_white)) {
        texttexture.render(61, 484);
    }
    if (loadText(pathfont, "If you are in mode 2 or 3, you will be", 27, textColor_white)) {
        texttexture.render(55, 509);
    }
    if (loadText(pathfont, "the player 2.", 27, textColor_white)) {
        texttexture.render(200, 534);
    }
    if (loadText(pathfont, "ENJOY NIM GAME!", 28, textColor_red)) {
        texttexture.render(150, 570);
    }

    nextnode.render(217, 625);

    SDL_RenderPresent(renderer);

}


/* 379 - 441
 * Case 3 : Set up your game
 * take a Game as a parameter
 * output: render backgr, nodes,... of case 3
 * use function loadText to load and member function render of LTexture to render.
 */

void setup(const struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //render backgr
    background[0].render(0,0);
    if (loadText(pathfont, "Set up your game", 60, textColor_white)) {
        texttexture.render(45, 10);
    }

    //play mode
    if (loadText(pathfont, "Play mode", 37, textColor_white)) {
        texttexture.render(70, 180);
    }
    minusnode.render(280,190);
    text_input.render(320, 200);
    plusnode.render(385,190);

    //(number) play mode now
    const char* s = to_string(yourGame.playMode).c_str();
    char tmp[3];
    strcpy(tmp, s); // const char* -> char* to use follow function
    if (loadText(pathfont, tmp, 36, textColor_white)) {
        texttexture.render(338, 184);
    }

    //game level
    if (loadText(pathfont, "Game level", 37, textColor_white)) {
        texttexture.render(70, 250);
    }
    minusnode.render(280,260);
    text_input.render(320, 270);
    plusnode.render(385,260);

    //(number) game level now
    s = to_string(yourGame.level).c_str();
    strcpy(tmp, s); // const char* -> char* to use follow function
    if (loadText(pathfont, tmp, 36, textColor_white)) {
        texttexture.render(332, 254);
    }

    //first turn
    if (loadText(pathfont, "First turn", 37, textColor_white)) {
        texttexture.render(70, 320);
    }
    minusnode.render(280,330);
    text_input.render(320, 340);
    plusnode.render(385,330);

    //who is fisrt turn now
    s = to_string(yourGame.firstturn).c_str();
    strcpy(tmp, s); // const char* -> char* to use follow function
    if (loadText(pathfont, tmp, 36, textColor_white)) {
        texttexture.render(338, 324);
    }

    //render node to finish set up
    nextnode.render(216, 450);

    SDL_RenderPresent(renderer);

}

/* 450 - 523
 * Case 4 : main screen based on level
 * take a Game as a parameter
 * output: render backgr, function nodes, bricks, name of players,... based on fixed parameter of the game
 * use function loadText to load and member function render of LTexture to render.
 */

void level(const struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //render backgr based on level of the game
    if (yourGame.level == 1 || yourGame.level == 2 || yourGame.level == 3) background[2].render(0,0);
    else if (yourGame.level == 4 || yourGame.level == 5 || yourGame.level == 6) background[3].render(0,0);
    else if (yourGame.level == 7 || yourGame.level == 8 || yourGame.level == 9) background[4].render(0,0);
    else if (yourGame.level == 10 || yourGame.level == 11 || yourGame.level == 12) background[5].render(0,0);
    else if (yourGame.level == 13 || yourGame.level == 14 || yourGame.level == 15) background[6].render(0,0);

    //render brick based on level of the game
    for (int i = 0; i < MAX_PILE; i++){
        for (int j = 0; j < MAX_BRICK; j++){
            if (yourGame.isrend[i][j]) yourGame.Stone[i][j].rend();
            if (yourGame.Stone[i][j].ren02) yourGame.Stone[i][j].brick02.render(yourGame.Stone[i][j].mPosition.x, yourGame.Stone[i][j].mPosition.y-3);
        }
    }

    //render function nodes
    hint.render(25,597);
    menu.render(456,599);
    nextnode.render(223,627);

    //render text about Level and Mode
    const char* s = to_string(yourGame.playMode).c_str();
    char tmp[8] = "Mode: ";
    strcat(tmp, s);
    if (loadText(pathfont, tmp, 24, textColor_white)) {
        texttexture.render(412, -2);
    }

    s = to_string(yourGame.level).c_str();
    char l[9] = "Level ";
    strcat(l,s);
    if (loadText(pathfont, l, 31, textColor_white)) {
        texttexture.render(223, -7);
    }

    //render active status of player
    if (yourGame.human1.Isyourturn || yourGame.AI.Isyourturn || yourGame.smart.Isyourturn) {
        active.render(132, 520);
        unactive.render(366,520);
    }
    else  {
        unactive.render(132, 520);
        active.render(366,520);
    }

    //render name of players
    if (yourGame.human1.play) {
        if (loadText(pathfont, "Player 1", 24, textColor_white)) {
            texttexture.render(112, 577);
        }
    }
    else if (yourGame.AI.play){
        if (loadText(pathfont, "AI", 24, textColor_white)) {
            texttexture.render(140, 577);
        }
    }
    else if (yourGame.smart.play) {
        if (loadText(pathfont, "SmartAI", 24, textColor_white)) {
            texttexture.render(112, 577);
        }
    }

    if (loadText(pathfont, "Player 2", 24, textColor_white)) {
        texttexture.render(344, 577);
    }

    SDL_RenderPresent(renderer);

}


/* 533 - 645
 * Case 5: announce the winner
 * take a Game as a parameter
 * output: render backgr, congratulation, text nodes... based on fixed parameter of the game
 * use function loadText to load and member function render of LTexture to render.
 */

void winner(const struct Game &yourGame){
    //load backgr case 5
    background[0].render(0,0);
    background[1].render(0,0);

    //announ the winnwr : load text

    if (yourGame.human1.Isthewinner){
        if (loadText(pathfont, "Congratulation!!!", 30, textColor_white)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28, textColor_white)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "Player 1", 32, textColor_white)) {
            texttexture.render(217, 260);
        }
    }
    else if (yourGame.human2.Isthewinner && yourGame.select){
        if (loadText(pathfont, "Congratulation!!!", 30, textColor_white)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28, textColor_white)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "Player 2", 32, textColor_white)) {
            texttexture.render(217, 260);
        }
    }
    else if (yourGame.AI.Isthewinner) {
        if (loadText(pathfont, "Congratulation!!!", 30, textColor_white)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28, textColor_white)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "AIPlayer", 32, textColor_white)) {
            texttexture.render(200, 260);
        }
    }
    else if (yourGame.smart.Isthewinner) {
        if (loadText(pathfont, "Congratulation!!!", 30, textColor_white)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28, textColor_white)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "SmartAIPlayer", 32, textColor_white)) {
            texttexture.render(167, 260);
        }
    }

    //load text node. if mouse position is in text node, this text will be rendered in red color.
    //get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //check if mourse is in button
    bool inNext = true;
    bool inquit = true;
    bool inMenu = true;
    if (x < 241) inquit = false;
    else if (x > 241 + 52) inquit = false;
    else if (y < 438) inquit = false;
    else if (y > 438 + 23) inquit = false;

    if (x < 212) inNext = false;
    else if (x > 212 + 127) inNext = false;
    else if (y < 332) inNext = false;
    else if (y > 332 + 26) inNext = false;

    if (x < 238) inMenu = false;
    else if (x > 238 + 70) inMenu = false;
    else if (y < 378) inMenu = false;
    else if (y > 378 + 26) inMenu = false;


    if (inNext){
        if (loadText(pathfont, "Next level", 28, textColor_red)) {
            texttexture.render(212, 318);
        }
    }
    else {
        if (loadText(pathfont, "Next level", 28, textColor_white)) {
            texttexture.render(212, 318);
        }
    }

    if (inMenu){
        if (loadText(pathfont, "Menu", 28, textColor_red)) {
            texttexture.render(238, 365);
        }
    }
    else {
        if (loadText(pathfont, "Menu", 28, textColor_white)) {
            texttexture.render(238, 365);
        }
    }

    if (inquit){
        if (loadText(pathfont, "Quit", 28, textColor_red)) {
            texttexture.render(241, 420);
        }
    }
    else {
        if (loadText(pathfont, "Quit", 28, textColor_white)) {
            texttexture.render(241, 420);
        }
    }

    //update screen
    SDL_RenderPresent(renderer);
}


/* 654 - 695
 * Case 1 : Welcome to Nim game -> handle when Wincase == 1
 * the 1st parameter is main pointer SDL_Event. the 2nd is WinCase and the last paremeter is quit (= true -> quit game)
 * output: change WinCase (go to read rules or start set up game or quit)
 */

void handleEventCase1(SDL_Event* e, int &WinCase, bool &quit){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button
        bool inhelp = true;
        bool instart = true;
        bool inquit = true;
        if (x < 199) inquit = false;
        else if (x > 199 + 100) inquit = false;
        else if (y < 440) inquit = false;
        else if (y > 440 + 40) inquit = false;

        if (x < 199) inhelp = false;
        else if (x > 199 + 111) inhelp = false;
        else if (y < 360) inhelp = false;
        else if (y > 360 + 60) inhelp = false;

        if (x < 199) instart = false;
        else if (x > 199 + 120) instart = false;
        else if (y < 300) instart = false;
        else if (y > 300 + 40) instart = false;

        if (inquit) {

            quit = true;
            Mix_PlayChannel(-1, selectNode, 0);

        }
        else if (inhelp) {
            WinCase = 2;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (instart) {
            WinCase = 3;
            Mix_PlayChannel(-1, selectNode, 0);
        }
    }
}


/* 704 - 723
 * Case 2 : Instructions -> handle when Wincase == 2
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase.
 * output: change WinCase (read rules complete and come to set up game)
 */

void handleEventCase2(SDL_Event* e, int &WinCase){
//if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button
        bool inNext = true;
        if (x < 214) inNext = false;
        else if (x > 214 + 103) inNext = false;
        else if (y < 625) inNext = false;
        else if (y > 625 + 26) inNext = false;

        if (inNext) {
            WinCase = 1;
            Mix_PlayChannel(-1, selectNode, 0);
        }
    }
}

/* 731 - 827
 * Case 3 : Set up your game -> handle when Wincase == 3
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase and the last parameter is a Game
 * output: update the Game and change WinCase (set up completed)
 * use member functions of game to update game
 */

void handleEventCase3(SDL_Event* e, int &WinCase, struct Game &yourGame){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is in button

        //mode
        bool modeMinus = true;
        bool modePlus = true;
        if (x < 280) modeMinus = false;
        else if (x > 280 + 33) modeMinus = false;
        else if (y < 200) modeMinus = false;
        else if (y > 200 + 33) modeMinus = false;

        if (x < 383) modePlus = false;
        else if (x > 383 + 33) modePlus = false;
        else if (y < 200) modePlus = false;
        else if (y > 200 + 33) modePlus = false;

        //level
        bool levelMinus = true;
        bool levelPlus = true;
        if (x < 280) levelMinus = false;
        else if (x > 280 + 33) levelMinus = false;
        else if (y < 270) levelMinus = false;
        else if (y > 270 + 33) levelMinus = false;

        if (x < 383) levelPlus = false;
        else if (x > 383 + 33) levelPlus = false;
        else if (y < 270) levelPlus = false;
        else if (y > 270 + 33) levelPlus = false;

        //first turn
        bool turnMinus = true;
        bool turnPlus = true;
        if (x < 280) turnMinus = false;
        else if (x > 280 + 33) turnMinus = false;
        else if (y < 340) turnMinus = false;
        else if (y > 340 + 33) turnMinus = false;

        if (x < 383) turnPlus = false;
        else if (x > 383 + 33) turnPlus = false;
        else if (y < 340) turnPlus = false;
        else if (y > 340 + 33) turnPlus = false;

        //next
        bool inNext = true;
        if (x < 216) inNext = false;
        else if (x > 216 + 100) inNext = false;
        else if (y < 450) inNext = false;
        else if (y > 450 + 29) inNext = false;

        if (modeMinus && (yourGame.playMode > 1)) {
            yourGame.playMode--;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (modePlus && (yourGame.playMode < 3)) {
            yourGame.playMode++;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (levelMinus && (yourGame.level > 1)) {
            yourGame.level--;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (levelPlus && (yourGame.level < 15)) {
            yourGame.level++;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (turnMinus && yourGame.firstturn > 1) {
            yourGame.firstturn--;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (turnPlus && (yourGame.firstturn < 2)) {
            yourGame.firstturn++;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (inNext){
            //set up default the others parameter of game
            yourGame.NPiles = 0;
            yourGame.NStones.clear();
            yourGame.select = false;
            yourGame.pileNow = -1;


            yourGame.setbrick();
            yourGame.setPlayers();
            yourGame.setStones();
            yourGame.setIsrend();

            WinCase = 4;
            Mix_PlayChannel(-1, selectNode, 0);
        }
    }
}


/* 837 - 1406
 * Case 4 : main screen based on level -> handle when Wincase == 4
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase and the last parameter is a Game
 * output: update the Game and change WinCase (if have a winner)
 * handle based on play mode of game
 */
void handleEventCase4(SDL_Event* e, int &WinCase, struct Game &yourGame) {
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION) {
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        switch (yourGame.playMode) {

            /* 849 - 1085
             * human VS human
             */
            case 1: {
                //do not render all bigger bricks
                for (int i = 0; i < MAX_PILE; i++){
                    for (int j = 0; j < MAX_BRICK; j++){
                        yourGame.Stone[i][j].ren02 = false;
                    }
                }

                /* 860 - 968
                 * if is player1 's turn
                 */
                if (yourGame.human1.Isyourturn) {

                    //set truepile (effective if it has just switched turn)
                    for (int i = 0; i < MAX_PILE; i++){
                        for (int j = 0; j < MAX_BRICK ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //if no bricks are selected in this turn -> care about the first brick selected -> set new truePile
                    if (!yourGame.select) {
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            //care about the last brick in each row
                            int j = yourGame.NStones[i]-1;

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight) inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1; //determine the pile could be selected in this turn
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truePile after determine the pile could be selected in this turn
                    for (int i = 0; i < MAX_PILE ; i++){
                        for (int j = 0; j < MAX_BRICK ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //handelEvent for each brick
                    for (int i = 0; i < MAX_PILE; i++){
                        for (int j = 0; j < MAX_BRICK ; j++){
                            if ((i < yourGame.NPiles) && (j < yourGame.NStones[i])) yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }


                    //if hint node be selected
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    //the hint node works only if there are no bricks has been selected
                    if (!yourGame.select && inHint && yourGame.human1.hint && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human1.hint = false;
                        yourGame.human1.Isyourturn = false;
                        yourGame.human2.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //if menu node be selected
                    //check if mourse is menu button
                    bool inmenu = true;
                    if (x < 455) inmenu = false;
                    else if (x > 455 + 60) inmenu = false;
                    else if (y < 597) inmenu = false;
                    else if (y > 597 + 60) inmenu = false;

                    if (inmenu && e->type == SDL_MOUSEBUTTONUP){
                        WinCase = 1;
                        Mix_PlayChannel(-1, selectNode, 0);
                    }

                    //if next node be selected
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    //the next node works only if at least 1 brick has been selected
                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human1.Isyourturn = false;
                        yourGame.human2.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //check winner
                    if (yourGame.checkWin()) {
                        yourGame.human1.Isthewinner = true;
                        yourGame.human2.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }

                }

                /* 970 - 1082
                * if is player2 's turn
                */
                else if (yourGame.human2.Isyourturn) {

                    //set truepile (effective if it has just switched turn)
                    for (int i = 0; i < MAX_PILE; i++){
                        for (int j = 0; j < MAX_BRICK ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //if no bricks are selected in this turn -> care about the first brick selected -> set new truePile
                    if (!yourGame.select) {
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            //care about the last brick in each row
                            int j = yourGame.NStones[i]-1;

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight) inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1; //determine the pile could be selected in this turn
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truePile after determine the pile could be selected in this turn
                    for (int i = 0; i < MAX_PILE ; i++){
                        for (int j = 0; j < MAX_BRICK ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //handelEvent for each brick
                    for (int i = 0; i < MAX_PILE; i++){
                        for (int j = 0; j < MAX_BRICK ; j++){
                            if ((i < yourGame.NPiles) && (j < yourGame.NStones[i])) yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }


                    //if hint node be selected
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    //the hint node works only if there are no bricks has been selected
                    if (!yourGame.select && inHint && yourGame.human2.hint && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.hint = false;
                        yourGame.human2.Isyourturn = false;
                        yourGame.human1.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //if menu node be selected
                    //check if mourse is menu button
                    bool inmenu = true;
                    if (x < 455) inmenu = false;
                    else if (x > 455 + 60) inmenu = false;
                    else if (y < 597) inmenu = false;
                    else if (y > 597 + 60) inmenu = false;

                    if (inmenu && e->type == SDL_MOUSEBUTTONUP){
                        WinCase = 1;
                        Mix_PlayChannel(-1, selectNode, 0);
                    }

                    //if next node be selected
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    //the next node works only if at least 1 brick has been selected
                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.Isyourturn = false;
                        yourGame.human1.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //check winner
                    if (yourGame.checkWin()) {
                        yourGame.human2.Isthewinner = true;
                        yourGame.human1.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }

                }

                break;
            }


            /* 1087 - 1245
            * AI VS human
            */
            case 2: {
                //do not render all bigger bricks
                for (int i = 0; i < MAX_PILE; i++) {
                    for (int j = 0; j < MAX_BRICK; j++) {
                        yourGame.Stone[i][j].ren02 = false;
                    }
                }

                /* 1101 - 1127
                 * if is AI's turn
                 */
                if (yourGame.AI.Isyourturn) {

                    //compute the step of AI - use member function of struct AIPlayer
                    yourGame.AI.move(yourGame.NStones);

                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            yourGame.isrend[i][j] = (i < yourGame.NPiles && j < yourGame.NStones[i]);
                        }
                    }
                    Mix_PlayChannel(-1, selectBrick, 0);

                    //switch turn after moves
                    yourGame.AI.Isyourturn = false;
                    yourGame.human2.Isyourturn = true;
                    yourGame.select = false;
                    yourGame.pileNow = -1;
                    Mix_PlayChannel(-1, switchTurn, 0);

                    //check winner
                    if (yourGame.checkWin()) {
                        yourGame.AI.Isthewinner = true;
                        yourGame.human2.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }
                }


                /* 1133 - 1244
                * if is player2 's turn
                */
                else if (yourGame.human2.Isyourturn) {

                    //set truepile (effective if it has just switched turn)
                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //if no bricks are selected in this turn -> care about the first brick selected -> set new truePile
                    if (!yourGame.select) {
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            //care about the last brick in each row
                            int j = yourGame.NStones[i] - 1;

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight)
                                inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1; //determine the pile could be selected in this turn
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truePile after determine the pile could be selected in this turn
                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //handelEvent for each brick
                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            if ((i < yourGame.NPiles) && (j < yourGame.NStones[i]))
                                yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }


                    //if hint node be selected
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    //the hint node works only if there are no bricks has been selected
                    if (!yourGame.select && inHint && yourGame.human2.hint && e->type == SDL_MOUSEBUTTONUP) {
                        yourGame.human2.hint = false;
                        yourGame.human2.Isyourturn = false;
                        yourGame.AI.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //if menu node be selected
                    //check if mourse is menu button
                    bool inmenu = true;
                    if (x < 455) inmenu = false;
                    else if (x > 455 + 60) inmenu = false;
                    else if (y < 597) inmenu = false;
                    else if (y > 597 + 60) inmenu = false;

                    if (inmenu && e->type == SDL_MOUSEBUTTONUP) {
                        WinCase = 1;
                        Mix_PlayChannel(-1, selectNode, 0);
                    }

                    //if next node be selected
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    //the next node works only if at least 1 brick has been selected
                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP) {
                        yourGame.human2.Isyourturn = false;
                        yourGame.AI.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //check winner
                    if (yourGame.checkWin()) {
                        yourGame.human2.Isthewinner = true;
                        yourGame.AI.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }
                }
                break;
            }

            /* 1250 - 1403
            * SmartAI VS human
            */
            case 3: {
                //do not render all bigger bricks
                for (int i = 0; i < MAX_PILE; i++) {
                    for (int j = 0; j < MAX_BRICK; j++) {
                        yourGame.Stone[i][j].ren02 = false;
                    }
                }

                /* 1261 - 1286
                 * if is SmartAI's turn
                 */
                if (yourGame.smart.Isyourturn) {
                    //compute the step of SmartAI - use member function of struct SmartAIPlayer
                    yourGame.smart.move(yourGame.NStones);

                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            yourGame.isrend[i][j] = (i < yourGame.NPiles && j < yourGame.NStones[i]);
                        }
                    }
                    Mix_PlayChannel(-1, selectBrick, 0);

                    //switch turn after moves
                    yourGame.smart.Isyourturn = false;
                    yourGame.human2.Isyourturn = true;
                    yourGame.select = false;
                    yourGame.pileNow = -1;
                    Mix_PlayChannel(-1, switchTurn, 0);

                    //check winner
                    if (yourGame.checkWin()) {
                        yourGame.smart.Isthewinner = true;
                        yourGame.human2.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }
                }

                /* 1291 - 1402
                * if is player2 's turn
                */
                else if (yourGame.human2.Isyourturn) {

                    //set truepile (effective if it has just switched turn)
                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //if no bricks are selected in this turn -> care about the first brick selected -> set new truePile
                    if (!yourGame.select) {
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            //care about the last brick in each row
                            int j = yourGame.NStones[i] - 1;

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight)
                                inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1; //determine the pile could be selected in this turn
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truePile after determine the pile could be selected in this turn
                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //handelEvent for each brick
                    for (int i = 0; i < MAX_PILE; i++) {
                        for (int j = 0; j < MAX_BRICK; j++) {
                            if ((i < yourGame.NPiles) && (j < yourGame.NStones[i]))
                                yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }


                    //if hint node be selected
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    //the hint node works only if there are no bricks has been selected
                    if (!yourGame.select && inHint && yourGame.human2.hint && e->type == SDL_MOUSEBUTTONUP) {
                        yourGame.human2.hint = false;
                        yourGame.human2.Isyourturn = false;
                        yourGame.smart.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //if menu node be selected
                    //check if mourse is menu button
                    bool inmenu = true;
                    if (x < 455) inmenu = false;
                    else if (x > 455 + 60) inmenu = false;
                    else if (y < 597) inmenu = false;
                    else if (y > 597 + 60) inmenu = false;

                    if (inmenu && e->type == SDL_MOUSEBUTTONUP) {
                        WinCase = 1;
                        Mix_PlayChannel(-1, selectNode, 0);
                    }

                    //if next node be selected
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    //the next node works only if at least 1 brick has been selected
                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP) {
                        yourGame.human2.Isyourturn = false;
                        yourGame.smart.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //check winner
                    if (yourGame.checkWin()) {
                        yourGame.human2.Isthewinner = true;
                        yourGame.smart.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }

                }

                break;
            }
        }
    }
}


/* 1415 - 1472
 * Case 5: announce the winner -> handle when Wincase == 5
 * the 1st parameter is main pointer SDL_Event. The 2nd is WinCase. The 3rd parameter is a Game and the last paremeter is quit (= true -> quit game).
 * output: change WinCase (based on player) and reset game.
 */

void handleEventCase5(SDL_Event* e, int &WinCase, struct Game &yourGame, bool &quit){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is in button
        bool inNext = true;
        bool inquit = true;
        bool inMenu = true;
        if (x < 241) inquit = false;
        else if (x > 241 + 52) inquit = false;
        else if (y < 438) inquit = false;
        else if (y > 438 + 23) inquit = false;

        if (x < 212) inNext = false;
        else if (x > 212 + 127) inNext = false;
        else if (y < 332) inNext = false;
        else if (y > 332 + 26) inNext = false;

        if (x < 238) inMenu = false;
        else if (x > 238 + 70) inMenu = false;
        else if (y < 378) inMenu = false;
        else if (y > 378 + 26) inMenu = false;

        //quit game
        if (inquit) {
            quit = true;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        //come back menu window
        else if (inMenu) {
            WinCase = 1;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        //next level -> reset game
        else if (inNext) {
            WinCase = 4;
            Mix_PlayChannel(-1, selectNode, 0);

            if (yourGame.human1.Isthewinner || yourGame.AI.Isthewinner || yourGame.smart.Isthewinner) yourGame.firstturn = 1;
            else yourGame.firstturn = 2;

            yourGame.NPiles = 0;
            yourGame.NStones.clear();
            if (yourGame.level<15) yourGame.level++;
            else yourGame.level = 1;
            yourGame.select = false;
            yourGame.pileNow = -1;

            yourGame.setStones();
            yourGame.setIsrend();
            yourGame.setbrick();
            yourGame.setPlayers();
        }
    }
}
