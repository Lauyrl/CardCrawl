#include "rest.h"

void Game::display_rest()
{
    if (restInit) 
    {
        Option::selected = false;
        restInit = false;
    }
    SDL_Rect clip = {0, 0, 1920, 1130};
    render_img("assets/scene/rest_scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &clip);
    render_img("assets/scene/shoulder.png", 0, 80, 1240, 760, 255, NULL);
    sleepOp.display();
    sleepOp.effect();
    panel.display();
}

bool Option::selected = false;
const map<restOption, const char*> Option::opMap = {
    {sleep, "assets/map/sleep.png"}
};
Option::Option(restOption op_) : Gui(400, 100, 250, 260)
{
    op = op_;
}
void Option::display()
{
    game.render_img(opMap.at(op), rect.x, rect.y, rect.w, rect.h, 255, NULL);
}
void Option::effect()
{
    if (!selected && detect_click()) 
    {
        if (op == sleep) 
        {
            selected = true;
            ironclad.heal(10);
            game.state_switch(game.gameStates::map);
        }
    }
}
