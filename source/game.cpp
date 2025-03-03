#include "game.h"

using namespace std;

int Game::tick = 0;
Game::Game(const char* title, int posX, int posY, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        if (!init_window(title, posX, posY, width, height)) return;
        isRunning = true;
    }
    else
    {
        cerr << "Game initialization failed. " << SDL_GetError();
        isRunning = false;
        return;
    } 
}

Game::~Game()
{
    cout << "Cleaning began." << endl;
    cleanup_textures();
    cout << "Textures cleaned." << endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cout << "Renderer and window cleaned." << endl;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    cout << "Game cleaned." << endl;
}

void Game::update()
{
    if (gameState == 2) display_battle();
}

void Game::clear_render()
{
    SDL_SetRenderDrawColor(renderer, 25, 50, 0, 100);
    SDL_RenderClear(renderer);
}

void Game::present_render()
{
    SDL_RenderPresent(renderer);
}

void Game::cleanup_textures()
{
    for (auto& thing:textureMap)
    {
        if (thing.second)
        {
            SDL_DestroyTexture(thing.second);
            thing.second = NULL;
        }
    }
    for (auto& thing:textTextureMap)
    {
        if (thing.second)
        {
            SDL_DestroyTexture(thing.second);
            thing.second = NULL;
        }
    }
    for (auto& thing:fontMap)
    {
        if (thing.second)
        {
            TTF_CloseFont(thing.second);
            thing.second = NULL;
        }
    }
}
