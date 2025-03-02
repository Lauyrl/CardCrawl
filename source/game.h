#pragma once

#include <iostream>
#include <map>
#include <string>
#include "../incl/libraries.h"
#include "../incl/constants.h"

class Game 
{
    public:
        Game(const char* title, int xpos, int ypos, int w, int h);
        ~Game();
        bool init_window(const char* title, int xpos, int ypos, int w, int h);
        bool running() {return isRunning;}
        void handle_events();
        void clear_render();
        void update();
        void present_render();

        SDL_Texture* load_texture(const char *filename);
        void render_img(const char *filename, int des_x, int des_y, int des_w, int des_h, SDL_Rect* clip);
        void cleanup_textures();

        bool battleStart{1};
        void display_battle();

        int gameState{2};
        
        bool isRunning;

        std::map<int, TTF_Font*> fontMap;
        std::map<std::string, SDL_Texture*> textureMap;
        std::map<std::string, SDL_Texture*> textTextureMap;
        SDL_Window* window;
        SDL_Renderer* renderer;

        static int timeDelta;
};
