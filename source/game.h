#pragma once

#include <map>
#include <random>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
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
        bool isRunning;

        SDL_Texture* load_texture(const char *filename);
        void render_img(const char *filename, int posX, int posY, int width, int height, Uint8 alpha, SDL_Rect* clip);
        void cleanup_textures();

        enum gameStates {
            start_menu, map, combat, event, rest, shop
        };
        int gameState{map};
        bool combatInit{true};
        bool mapGenerated{false};
        bool restInit{true};
        bool eventInit{true};
        bool shopInit{true};
        void state_switch(gameStates state);
        void display_map();
        void display_rest();
        void display_shop();
        void display_event();
        void display_combat();

        std::map<int, TTF_Font*> fontMap;
        std::map<std::string, SDL_Texture*> textureMap;
        std::map<std::string, SDL_Texture*> textTextureMap;
        SDL_Window* window;
        SDL_Renderer* renderer;
};
template <typename T>
void shuffle_vector(std::vector<T> &vector)
{
    static std::random_device seed;                 //initialized once
    static std::default_random_engine rng(seed());  //retains state while out of scope
    std::ranges::shuffle(vector, rng);
}

extern Game game;
