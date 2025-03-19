#include "game.h"

using namespace std;

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
    if (gameState == map) display_map();
    if (gameState == rest) display_rest();
    if (gameState == shop) display_shop();
    if (gameState == event) display_event();
    if (gameState == combat) display_combat();
    if (gameState == treasure) display_treasure();
}

void Game::clear_render()
{
    SDL_SetRenderDrawColor(renderer, 200, 150, 100, 200);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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

int rand_int(int min, int max)
{
    static std::random_device seed;
    static std::mt19937 mt(seed());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
