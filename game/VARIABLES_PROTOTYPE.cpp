//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "VARIABLES_PROTOTYPE.h"
//init
bool init(){
    bool success = true;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
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

            }
        }
    }
    return success;
}

SDL_Texture* loadTexture(char* pathImage){
    //the final texture
    SDL_Texture* newTexture = nullptr;

    //Load image
    SDL_Surface* loadedSurface = IMG_Load(pathImage);
    if (loadedSurface == nullptr){
        cout << "Failed to load image " << pathImage << ". SDL_image Error: " << IMG_GetError();
    }
    else {
        //create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr){
            cout << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadImage(char* pathImage){
    bool success = true;
    Texture = loadTexture(pathImage);
    if (Texture == nullptr){
        cout << "Failed to load texture image!" << endl;
        success = false;
    }
    return success;
}

bool loadText(char* pathFont, char* text, int size){
    bool success = true;
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

//Frees media and shuts down SDl
void close(){
    brick.free();
    Backgr.free();
    active.free();
    unactive.free();
    Node.free();

    TTF_CloseFont(font);
    font = nullptr;

    SDL_DestroyTexture(Texture);
    Texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

vector<int> chooseLevel(const char* f, int level, vector<vector<int>>data){
    int num = level-1;
    vector<int>a;
    for (int i=0; i<data[num][0];i++){
        a.push_back(data[num][i+1]);
    }
    return a;
}

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

