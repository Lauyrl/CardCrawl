#include "../../incl/libraries.h"
#include "../game.h"

const bool FALSE = 0;
const bool TRUE  = 1;

using namespace std;

bool Game::init_window(const char* title, int xpos, int ypos, int w, int h, unsigned int flag)
{
    window = SDL_CreateWindow(title, xpos, ypos, w, h, flag);
    if (!window) 
    {   
        cerr << "Window creation failed. " << SDL_GetError();
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        cerr << "Rendering failed. " << SDL_GetError();
        return FALSE;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cerr << "Failed to initialize SDL_image " << SDL_GetError();
        return FALSE;
    }
    if (TTF_Init() == -1)
    {
        cerr << "Failed to initialize SDL_ttf for " << SDL_GetError();
        return FALSE;
    }
    return TRUE;
}

