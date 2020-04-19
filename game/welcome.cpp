//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "welcome.h"
using namespace std;

void welcometogame(){

        //load media
        extern char* path;
        path = "../image/color-01.png";
        char* pathfont = "../font/Xerox Sans Serif Narrow.ttf";
        //image = loadSurface(path);

        //apply the image
        //SDL_BlitSurface(image, nullptr, screenSurface, nullptr);
        //Update
        //SDL_UpdateWindowSurface(window);

        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            if (loadText(pathfont, "welcome to NIM game", 28)) {
                //render texture to screen
                //SDL_Rect Message = {100, 100, 500, 500};

                //SDL_RenderCopy(renderer, Texture, nullptr, &Message);
                texttexture.render(( SCREEN_WIDTH - texttexture.getWidth() ) / 2, ( SCREEN_HEIGHT - texttexture.getHeight() ) / 2);
            }
           //update
            SDL_RenderPresent(renderer);

            eloop();
        }

    //free resourses and close
    //close();
}
