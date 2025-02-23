#include "game.h"
#include "character/character.h"

using namespace std; 

Game game("CardCrawl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);

const int FPS = 60;
const int frameDelay = 1000/FPS;
Uint32 frameStart;
Uint32 frameTime;

Character ironclad = Character(100);

int main(int argc, char* argv[]) 
{
    while (game.running())
    {
        frameStart = SDL_GetTicks();

        game.handle_events();
        game.clear_render();
        game.update();
        game.present_render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
    return 0;
}

