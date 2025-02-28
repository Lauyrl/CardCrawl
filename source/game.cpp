#include "game.h"

using namespace std;

Game::Game(const char* title, int xpos, int ypos, int w, int h)
{
    unsigned int flag = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        if (!init_window(title, xpos, ypos, w, h, flag)) return;
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
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

