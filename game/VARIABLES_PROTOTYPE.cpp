//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "VARIABLES_PROTOTYPE.h"

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
            //screenSurface = SDL_GetWindowSurface(window);
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

//Load media
bool loadMedia(char* path){
    bool success = true;

    image = IMG_Load(path);
    if (image == nullptr){
        cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << endl;
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface(char* path){
    SDL_Surface* optimized = nullptr;
    if (!loadMedia(path)){
        cout << "Failed to load media!\n ";
    }
    else {
        //screenSurface = SDL_GetWindowSurface(window);
        optimized = SDL_ConvertSurface(image, screenSurface ->format,0); ///
        if (optimized == nullptr){
            cout << " Unable to optimize image! SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(image);
        image = nullptr;
    }
    return optimized;
}

SDL_Texture* loadTexture(char* path){
    //the final texture
    SDL_Texture* newTexture = nullptr;

    //Load image
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr){
        cout << "Failed to load image " << path << ". SDL_image Error: " << IMG_GetError();
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

bool loadImage(char* path){
    bool success = true;
    Texture = loadTexture(path);
    if (Texture == nullptr){
        cout << "Failed to load texture image!" << endl;
        success = false;
    }
    return success;
}

bool loadText(char* path, char* text){
    bool success = true;
    //open the font
    font = TTF_OpenFont(path, 28);
    if (font == nullptr){
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    else {
        //render text
        SDL_Color textColor = {0,0,0};
        if (!texttexture.loadFromRenderedText(text, textColor)){
            cout << "Failed to render text texture\n";
            success = false;
        }
    }
    return success;
}

void eloop(){
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
    }
}

//Frees media and shuts down SDl
void close(){
    brick.free();
    Backgr.free();
    active.free();

    TTF_CloseFont(font);
    font = nullptr;

    SDL_FreeSurface(image);
    image = nullptr;

    SDL_DestroyTexture(Texture);
    Texture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window); //se take care screensurface
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
