#include "game.h"
#include "gui/top_panel.h"

using namespace std;

Character ironclad(56);
TopPanel strip;
Game game("CardCrawl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);

const int FPS = 60;
const int frameDelay = 1000/FPS;
Uint32 frameStart;
Uint32 frameTime;

int main(int argc, char* argv[]) 
{
    while (game.running())
    {
        frameStart = SDL_GetTicks();

        game.handle_events();
        game.clear_render();
        game.update();
        //cout << "Update cost: " << SDL_GetTicks() - frameStart << endl;
        game.present_render();

        frameTime = SDL_GetTicks() - frameStart;
        // cout << "Total: " << frameTime << endl << endl;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
    return 0;
}

