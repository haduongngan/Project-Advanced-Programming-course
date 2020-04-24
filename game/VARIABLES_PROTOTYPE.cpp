//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "VARIABLES_PROTOTYPE.h"
//init
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

//load Music
bool loadMusic(){
    bool succcess = true;

    //load music
    gMusic = Mix_LoadMUS("../music/08-Frappe-Snowland_-Sherbet-Land-_1_-_mp3cut.net_.ogg");
    if (gMusic == nullptr){
        cout << "Failed to load Frappe music! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    //load sound effect;
    selectBrick = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_pick_up_collect_item_sci_fi_004_46204.ogg");
    if (selectBrick == nullptr){
        cout << "Failed to load selectBrick sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    selectNode = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_musical_bright_ping_musical_short_positive_002_44884.ogg");
    if (selectNode == nullptr){
        cout << "Failed to load selectNode sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    win = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_fanfare_synthesized_brass_44793.ogg");
    if (win == nullptr){
        cout << "Failed to load win sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }

    switchTurn = Mix_LoadWAV("../music/zapsplat_multimedia_game_tone_bright_positive_002_44875.ogg");
    if (switchTurn == nullptr){
        cout << "Failed to load switchTurn sound! SDL_mixer Error: " << Mix_GetError() << endl;
        succcess = false;
    }
    return succcess;
}

//load Text mau trang
bool loadText(char* pathFont, char* text, int size){
    bool success = true;
    TTF_CloseFont(font);
    font = nullptr;
    //open the font
    font = TTF_OpenFont(pathFont, size);
    if (font == nullptr){
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    else {
        //render text
        SDL_Color textColor = {0xF8,0xF8,0xff};  //0xFF,0xFa,0xf0
        if (!texttexture.loadFromRenderedText(text, textColor)){
            cout << "Failed to render text texture\n";
            success = false;
        }
    }
    return success;
}

//load text mau do
bool loadTextNew(char* pathFont, char* text, int size){
    bool success = true;
    TTF_CloseFont(font);
    font = nullptr;
    //open the font
    font = TTF_OpenFont(pathFont, size);
    if (font == nullptr){
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    else {
        //render text
        SDL_Color textColor = {0xa5,0x2a,0x2a};  //0xFF,0xFa,0xf0
        if (!texttexture.loadFromRenderedText(text, textColor)){
            cout << "Failed to render text texture\n";
            success = false;
        }
    }
    return success;
}

//Frees media and shuts down SDl
void close(){
    active.free();
    unactive.free();
    hint.free();
    nextnode.free();
    minusnode.free();
    plusnode.free();
    text_input.free();
    menu.free();
    for (int i=0; i<7; i++){
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

    SDL_DestroyTexture(Texture);
    Texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

//tao mang luu so stones dua vao level
vector<int> chooseLevel(int level, vector<vector<int>>data){
    int num = level-1;
    vector<int>a;
    for (int i=0; i<data[num][0];i++){
        a.push_back(data[num][i+1]);
    }
    return a;
}

//doc du lieu tu Stones.txt
void loadData(const char* f){
    ifstream infile(f);
    string line;
    while(getline(infile,line)){
        vector<int>tmp;
        int value;
        stringstream iss(line);
        while(iss>>value){
            tmp.push_back(value);
        }
        data.push_back(tmp);
    }
}

//Case 1 : Welcome to Nim game
void welcome(struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    background[0].render(0,0);

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

    if (loadText(pathfont, "Welcome to", 60)) {
        texttexture.render(90, 60);
    }
    if (loadText(pathfont, "NIM GAME", 70)) {
        texttexture.render(150, 130);
    }

    if (instart){
        if (loadTextNew(pathfont, "Start", 52)) {
            texttexture.render(193, 270);
        }
    }
    else {
        if (loadText(pathfont, "Start", 52)) {
            texttexture.render(193, 270);
        }
    }
    if (inhelp){
        if (loadTextNew(pathfont, "Help", 52)) {
            texttexture.render(199, 340);
        }
    }
    else {
        if (loadText(pathfont, "Help", 52)) {
            texttexture.render(199, 340);
        }
    }
    if (inquit){
        if (loadTextNew(pathfont, "Quit", 52)) {
            texttexture.render(199, 410);
        }
    }
    else {
        if (loadText(pathfont, "Quit", 52)) {
            texttexture.render(199, 410);
        }
    }

    SDL_RenderPresent(renderer);

}

//Case 2 : Instructions
void help(struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    background[0].render(0,0);

    if (loadText(pathfont, "Instructions", 60)) {
        texttexture.render(90, 0);
    }

    if (loadText(pathfont, "Two players take turns removing bricks", 27)) {
        texttexture.render(30, 80);
    }
    if (loadText(pathfont, "from one of the rows that appear.", 27)) {
        texttexture.render(70, 105);
    }

    if (loadText(pathfont, "You must select at least one brick ", 27)) {
        texttexture.render(75, 139);
    }
    if (loadText(pathfont, "in your turn.", 27)) {
        texttexture.render(190, 164);
    }

    if (loadText(pathfont, "Click the NEXT button to", 27)) {
        texttexture.render(120, 198);
    }
    if (loadText(pathfont, "end your turn.", 27)) {
        texttexture.render(190, 223);
    }

    if (loadText(pathfont, "During the game, you can use", 27)) {
        texttexture.render(50, 257);
    }
    hint.render(400,257);
    if (loadText(pathfont, "(one time) to skip your turn.", 27)) {
        texttexture.render(65, 282);
    }

    if (loadText(pathfont, "The player removing the last", 27)) {
        texttexture.render(100, 316);
    }
    if (loadText(pathfont, "brick will win the game.", 27)) {
        texttexture.render(125, 341);
    }

    if (loadText(pathfont, "You can choose 1 of 3 play modes:", 27)) {
        texttexture.render(73, 375);
    }
    if (loadText(pathfont, "1. Player VS Player", 27)) {
        texttexture.render(150, 400);
    }
    if (loadText(pathfont, "2. Player VS AI", 27)) {
        texttexture.render(150, 425);
    }
    if (loadText(pathfont, "3. Player VS SmartAI", 27)) {
        texttexture.render(150, 450);
    }

    if (loadText(pathfont, "You are able choose who will take the first turn.", 27)) {
        texttexture.render(20, 484);
    }
    if (loadText(pathfont, "If you are in mode 2 or 3, you will be", 27)) {
        texttexture.render(55, 509);
    }
    if (loadText(pathfont, "the player 2.", 27)) {
        texttexture.render(200, 534);
    }
    if (loadTextNew(pathfont, "ENJOY NIM GAME!", 28)) {
        texttexture.render(150, 570);
    }

    nextnode.render(217, 625);

    SDL_RenderPresent(renderer);

}

//Case 3 : Set up your game
void setup(struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    background[0].render(0,0);
    if (loadText(pathfont, "Set up your game", 60)) {
        texttexture.render(45, 10);
    }

    if (loadText(pathfont, "Play mode", 37)) {
        texttexture.render(70, 180);
    }
    minusnode.render(280,190);
    text_input.render(320, 200);
    plusnode.render(385,190);
    const char* s = to_string(yourGame.playMode).c_str();
    char tmp[3];
    strcpy(tmp, s);
    if (loadText(pathfont, tmp, 36)) {
        texttexture.render(338, 184);
    }

    if (loadText(pathfont, "Game level", 37)) {
        texttexture.render(70, 250);
    }
    minusnode.render(280,260);
    text_input.render(320, 270);
    plusnode.render(385,260);
    s = to_string(yourGame.level).c_str();
    strcpy(tmp, s);
    if (loadText(pathfont, tmp, 36)) {
        texttexture.render(332, 254);
    }

    if (loadText(pathfont, "First turn", 37)) {
        texttexture.render(70, 320);
    }
    minusnode.render(280,330);
    text_input.render(320, 340);
    plusnode.render(385,330);
    s = to_string(yourGame.firstturn).c_str();
    strcpy(tmp, s);
    if (loadText(pathfont, tmp, 36)) {
        texttexture.render(338, 324);
    }

    nextnode.render(216, 450);

    SDL_RenderPresent(renderer);

}

//Case 4 : load back, brick, cac node,... theo level -> man hinh choi game
void level(struct Game &yourGame){
    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //rend backgr
    if (yourGame.level == 1 || yourGame.level == 2 || yourGame.level == 3) background[2].render(0,0);
    else if (yourGame.level == 4 || yourGame.level == 5 || yourGame.level == 6) background[3].render(0,0);
    else if (yourGame.level == 7 || yourGame.level == 8 || yourGame.level == 9) background[4].render(0,0);
    else if (yourGame.level == 10 || yourGame.level == 11 || yourGame.level == 12) background[5].render(0,0);
    else if (yourGame.level == 13 || yourGame.level == 14 || yourGame.level == 15) background[6].render(0,0);

    //rend brick
    for (int i=0; i<6; i++){
        for (int j=0; j<13; j++){
            if (yourGame.isrend[i][j]) yourGame.Stone[i][j].rend();
            if (yourGame.Stone[i][j].ren02) yourGame.Stone[i][j].brick02.render(yourGame.Stone[i][j].mPosition.x, yourGame.Stone[i][j].mPosition.y-3);
        }
    }

    //rend nodes
    hint.render(25,597);
    menu.render(456,599);
    nextnode.render(223,627);

    //rend text
    const char* s = to_string(yourGame.playMode).c_str();
    char tmp[8] = "Mode: ";
    strcat(tmp, s);
    if (loadText(pathfont, tmp, 24)) {
        texttexture.render(412, -2);
    }

    s = to_string(yourGame.level).c_str();
    char l[9] = "Level ";
    strcat(l,s);
    if (loadText(pathfont, l, 31)) {
        texttexture.render(223, -7);
    }

    //rend active
    if (yourGame.human1.Isyourturn || yourGame.AI.Isyourturn || yourGame.smart.Isyourturn) {
        active.render(132, 520);
        unactive.render(366,520);
    }
    else  {
        unactive.render(132, 520);
        active.render(366,520);
    }

    //rend name
    if (yourGame.human1.play) {
        if (loadText(pathfont, "Player 1", 24)) {
            texttexture.render(112, 577);
        }
    }
    else if (yourGame.AI.play){
        if (loadText(pathfont, "AI", 24)) {
            texttexture.render(140, 577);
        }
    }
    else if (yourGame.smart.play) {
        if (loadText(pathfont, "SmartAI", 24)) {
            texttexture.render(112, 577);
        }
    }

    if (loadText(pathfont, "Player 2", 24)) {
        texttexture.render(344, 577);
    }

    SDL_RenderPresent(renderer);

}

//Case 1 : Welcome to Nim game -> xu ky khi chon cac node
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

//Case 2 : Instructions -> xu ky khi chon cac node
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

//Case 3 : Set up your game -> xu ky khi chon cac node
void handleEventCase3(SDL_Event* e, int &WinCase, struct Game &yourGame){
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button

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
            //set up lai che do mac dinh nhung thong so khac
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

//Case 4 : man hinh choi game -> xu ky khi chon cac node, thao tac khi choi game
void handleEventCase4(SDL_Event* e, int &WinCase, struct Game &yourGame) {
    //if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION) {
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        switch (yourGame.playMode) {
            case 1: {   //human VS human
                for (int i=0; i<6; i++){
                    for (int j=0; j<13 ; j++){
                        yourGame.Stone[i][j].ren02 = false;
                    }
                }

                if (yourGame.human1.Isyourturn) { //turn cua nguoi 1

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    if (!yourGame.select) {
                        //xet vien brick duoc chon dau tien
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            int j = yourGame.NStones[i]-1; //xet vien cuoi cung moi hang

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight) inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                // cout << i+1 << " " << j+1 << " " << yourGame.isrend[i][j] << endl;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1;
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //neu chon brick
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            if ((i < yourGame.NPiles) && (j < yourGame.NStones[i])) yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }


                    //neu chon hint
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    if (!yourGame.select && inHint && yourGame.human1.hint && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human1.hint = false;
                        yourGame.human1.Isyourturn = false;
                        yourGame.human2.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //neu chon menu
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

                    //neu chon next
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human1.Isyourturn = false;
                        yourGame.human2.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    if (yourGame.checkWin()) {
                        yourGame.human1.Isthewinner = true;
                        yourGame.human2.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }

                }

                else if (yourGame.human2.Isyourturn) { //turn cua nguoi 2

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }



                    if (!yourGame.select) {
                        //xet vien brick duoc chon dau tien
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            int j = yourGame.NStones[i]-1; //xet vien cuoi cung moi hang

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight) inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                // cout << i+1 << " " << j+1 << " " << yourGame.isrend[i][j] << endl;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1;
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //neu chon brick
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            if ((j < yourGame.NStones[i]) && (i < yourGame.NPiles)) yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }

                    //neu chon hint
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    if (!yourGame.select && inHint && yourGame.human2.hint && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.hint = false;
                        yourGame.human2.Isyourturn = false;
                        yourGame.human1.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //neu chon menu
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

                    //neu chon next
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.Isyourturn = false;
                        yourGame.human1.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    if (yourGame.checkWin()) {
                        yourGame.human2.Isthewinner = true;
                        yourGame.human1.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }

                }

                break;
            }

            case 2: { //AI VS human
                for (int i=0; i<6; i++){
                    for (int j=0; j<13 ; j++){
                        yourGame.Stone[i][j].ren02 = false;
                    }
                }

                if (yourGame.AI.Isyourturn) { //turn cua nguoi 1
                    yourGame.AI.move(yourGame.NStones);
                    for (int i=0; i<6; i++) {
                        for (int j = 0; j < 13; j++) {
                            yourGame.isrend[i][j] = (i < yourGame.NPiles && j < yourGame.NStones[i]);
                        }
                    }
                    Mix_PlayChannel(-1, selectBrick, 0);

                    //doi turn sau khi di xong
                    yourGame.AI.Isyourturn = false;
                    yourGame.human2.Isyourturn = true;
                    yourGame.select = false;
                    yourGame.pileNow = -1;
                    Mix_PlayChannel(-1, switchTurn, 0);

                    if (yourGame.checkWin()) {
                        yourGame.AI.Isthewinner = true;
                        yourGame.human2.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }
                }

                else if (yourGame.human2.Isyourturn) { //turn cua nguoi 2

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }


                    if (!yourGame.select) {
                        //xet vien brick duoc chon dau tien
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            int j = yourGame.NStones[i]-1; //xet vien cuoi cung moi hang

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight) inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                // cout << i+1 << " " << j+1 << " " << yourGame.isrend[i][j] << endl;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1;
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //neu chon brick
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            if ((j < yourGame.NStones[i]) && (i < yourGame.NPiles)) yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }

                    //neu chon hint
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    if (!yourGame.select && inHint && yourGame.human2.hint && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.hint = false;
                        yourGame.human2.Isyourturn = false;
                        yourGame.AI.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //neu chon menu
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

                    //neu chon next
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.Isyourturn = false;
                        yourGame.AI.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    if (yourGame.checkWin()) {
                        yourGame.human2.Isthewinner = true;
                        yourGame.AI.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }

                }

                break;
            }

            case 3: { //smart VS human
                for (int i=0; i<6; i++){
                    for (int j=0; j<13 ; j++){
                        yourGame.Stone[i][j].ren02 = false;
                    }
                }

                if (yourGame.smart.Isyourturn) { //turn cua nguoi 1
                    yourGame.smart.move(yourGame.NStones);
                    for (int i=0; i<6; i++) {
                        for (int j = 0; j < 13; j++) {
                            yourGame.isrend[i][j] = i < yourGame.NPiles && j < yourGame.NStones[i];
                        }
                    }

                    Mix_PlayChannel(-1, selectBrick, 0);
                    //doi turn sau khi di xong
                    yourGame.smart.Isyourturn = false;
                    yourGame.human2.Isyourturn = true;
                    yourGame.select = false;
                    yourGame.pileNow = -1;
                    Mix_PlayChannel(-1, switchTurn, 0);

                    if (yourGame.checkWin()) {
                        yourGame.smart.Isthewinner = true;
                        yourGame.human2.Isthewinner = false;
                        WinCase = 5;
                        Mix_PlayChannel(-1, win, 0);
                    }
                }

                else if (yourGame.human2.Isyourturn) { //turn cua nguoi 2

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }



                    if (!yourGame.select) {
                        //xet vien brick duoc chon dau tien
                        for (int i = 0; i < yourGame.NPiles; i++) {
                            if (yourGame.select) break;

                            int j = yourGame.NStones[i]-1; //xet vien cuoi cung moi hang

                            bool inside = true;
                            if (x < yourGame.Stone[i][j].mPosition.x) inside = false;
                            else if (x > yourGame.Stone[i][j].mPosition.x + yourGame.Stone[i][j].mWidth) inside = false;
                            else if (y < yourGame.Stone[i][j].mPosition.y) inside = false;
                            else if (y > yourGame.Stone[i][j].mPosition.y + yourGame.Stone[i][j].mHeight) inside = false;

                            if (inside && e->type == SDL_MOUSEBUTTONUP) {
                                yourGame.Stone[i][j].ren = false;
                                yourGame.isrend[i][j] = false;
                                // cout << i+1 << " " << j+1 << " " << yourGame.isrend[i][j] << endl;
                                yourGame.select = true;
                                yourGame.NStones[i]--;
                                yourGame.pileNow = i + 1;
                                Mix_PlayChannel(-1, selectBrick, 0);
                                break;
                            }
                        }
                    }

                    //set truepile
                    for (int i=0; i<6; i++){
                        for (int j=0; j<13 ; j++){
                            yourGame.Stone[i][j].setTruepile(yourGame.pileNow);
                        }
                    }

                    //neu chon brick
                    for (int i=0; i < yourGame.NPiles; i++){
                        for (int j=0; j < yourGame.NStones[i] ; j++){
                            yourGame.Stone[i][j].handleEvent(e, yourGame.isrend, yourGame.NStones);
                        }
                    }

                    //neu chon hint
                    //check if mourse is hint button
                    bool inHint = true;
                    if (x < 25) inHint = false;
                    else if (x > 25 + 60) inHint = false;
                    else if (y < 597) inHint = false;
                    else if (y > 597 + 60) inHint = false;

                    if (!yourGame.select && inHint && yourGame.human2.hint && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.hint = false;
                        yourGame.human2.Isyourturn = false;
                        yourGame.smart.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

                    //neu chon menu
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

                    //neu chon next
                    //check if mourse is next button
                    bool inNext = true;
                    if (x < 223) inNext = false;
                    else if (x > 223 + 100) inNext = false;
                    else if (y < 627) inNext = false;
                    else if (y > 627 + 26) inNext = false;

                    if (yourGame.select && inNext && e->type == SDL_MOUSEBUTTONUP){
                        yourGame.human2.Isyourturn = false;
                        yourGame.smart.Isyourturn = true;
                        yourGame.select = false;
                        yourGame.pileNow = -1;
                        Mix_PlayChannel(-1, selectNode, 0);
                        Mix_PlayChannel(-1, switchTurn, 0);
                    }

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

//Case 5 : sau khi thong bao chien thang -> xu ky khi chon cac node: next level, quit, ...
void handleEventCase5(SDL_Event* e, int &WinCase, struct Game &yourGame, bool &quit){
//if mouse event happened
    if (e->type == SDL_MOUSEBUTTONUP){
        //get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //check if mourse is ib button
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

        if (inquit) {
            quit = true;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (inMenu) {
            WinCase = 1;
            Mix_PlayChannel(-1, selectNode, 0);
        }
        else if (inNext) {
            WinCase = 4;
            Mix_PlayChannel(-1, selectNode, 0);

            if (yourGame.human1.Isthewinner || yourGame.AI.Isthewinner || yourGame.smart.Isthewinner) yourGame.firstturn = 1;
            else yourGame.firstturn = 2;
            //setup lai
            yourGame.NPiles = 0;
            yourGame.NStones.clear();
            yourGame.level++;
            yourGame.select = false;
            yourGame.pileNow = -1;

            yourGame.setStones();
            yourGame.setIsrend();
            yourGame.setbrick();
            yourGame.setPlayers();
        }
    }
}
