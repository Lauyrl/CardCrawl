#include "rest.h"

void Game::display_rest()
{
    SDL_Rect clip = {0, 0, 1920, 1130};
    render_img("assets/scene/rest_scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &clip);
    render_img("assets/scene/shoulder.png", 0, 80, 1240, 760, 255, NULL);

    
}
