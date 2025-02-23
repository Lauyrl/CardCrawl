#include "../../../incl/libraries.h"
#include "cursor_variables.h"
#include "../../game.h"


void Game::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
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
                break;
            }
            case (SDL_MOUSEBUTTONDOWN):
            {
                if (event.button.button == SDL_BUTTON_LEFT) 
                {
                    clickQueued = true;
                }
                break;
            }
            case (SDL_MOUSEBUTTONUP):
            {
                if (event.button.button == SDL_BUTTON_LEFT) 
                {
                    clickQueued = false;
                }
                break;
            }
            default: 
                break;
        }
    }
}
