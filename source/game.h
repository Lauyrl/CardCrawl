#pragma once

#include <iostream>
#include <map>
#include <string>
#include "../incl/libraries.h"
#include "../incl/constants.h"

class Game 
{
    public:
        Game(const char* title, int posX, int posY, int width, int height);
        ~Game();
        bool init_window(const char* title, int posX, int posY, int width, int height);
        bool running() {return isRunning;}
        void handle_events();
        void clear_render();
        void update();
        void present_render();

        SDL_Texture* load_texture(const char *filename);
        void render_img(const char *filename, int posX, int posY, int width, int height, SDL_Rect* clip);
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

        static int tick;
};
