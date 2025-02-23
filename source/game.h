#pragma once

#include "../incl/libraries.h"
#include "../incl/constants.h"
#include <iostream>

class Game 
{
    public:
        Game(const char* title, int xpos, int ypos, int w, int h);
        ~Game();
        bool init_window(const char* title, int xpos, int ypos, int w, int h, unsigned int flag);
        void handle_events();
        void clear_render();
        void update();
        void present_render();
        bool running() {return isRunning;}

        SDL_Texture* load_texture(const char *filename);
        void render_texture(SDL_Texture *texture, int des_x, int des_y, int des_w, int des_h, SDL_Rect* clip);
        void render_img(const char *filename, int des_x, int des_y, int des_w, int des_h, SDL_Rect* clip);

        void display_battle();
        bool battleStart{1};

    private:
        bool isRunning;
        int gameState{2};
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* imageSurface;
        SDL_Surface* windowSurface;
};
