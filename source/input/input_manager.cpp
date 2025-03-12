#include "../../incl/libraries.h"
#include "cursor_variables.h"
#include "../game.h"


void Game::handle_events()
{
    SDL_Event event;
    clickQueued = false;
    if (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case (SDL_QUIT):
            {
                isRunning = false;
                break;
            }
            case (SDL_MOUSEMOTION):
            {
                SDL_GetMouseState(&cursorX, &cursorY);
                //std::cout << cursorX << ' ' << cursorY << std::endl;
                break;
            }
            case (SDL_MOUSEBUTTONDOWN):
            {
                if (clickReleased && event.button.button == SDL_BUTTON_LEFT) 
                {
                    clickQueued = true;
                    clickReleased = false;
                }
                break;
            }
            case (SDL_MOUSEBUTTONUP):
            {
                if (event.button.button == SDL_BUTTON_LEFT) 
                {
                    clickQueued = false;
                    clickReleased = true;
                }
                break;
            }
            default: 
                break;
        }
    }
}

void Game::state_switch(gameStates state)
{
    gameState = state;
    SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2+100, SCREEN_HEIGHT/2+200);
    cursorX = 0; cursorY = 0;
}
