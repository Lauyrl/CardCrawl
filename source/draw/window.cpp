#include "../../incl/libraries.h"
#include "../game.h"

using namespace std;

bool Game::init_window(const char* title, int xpos, int ypos, int w, int h)
{
    window = SDL_CreateWindow(title, xpos, ypos, w, h, SDL_WINDOW_RESIZABLE);
    if (!window) 
    {   
        cerr << "Window creation failed. " << SDL_GetError();
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) 
    {
        cerr << "Rendering failed. " << SDL_GetError();
        return false;
    }
    // cout << "Renderer created already" << endl;
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cerr << "Failed to initialize SDL_image " << IMG_GetError();
        return false;
    }
    if (TTF_Init() == -1)
    {
        cerr << "Failed to initialize SDL_ttf for " << TTF_GetError();
        return false;
    }
    return true;
}

