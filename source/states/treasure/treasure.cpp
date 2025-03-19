#include "treasure.h"

void Game::display_treasure()
{
    static RewardMenu rMenuTreasure = RewardMenu(true,true,false);
    static Chest chest;
    if (treasureInit)
    {
        int gMin, gMax, rUncomThres, rRareThres, rMax;
        chest.generate();
        if (chest.seed >= 0 && chest.seed < 5) 
        {
            gMin = 20; gMax = 28;
            rUncomThres = 15; rRareThres = 20; rMax = 19;
        }
        else if (chest.seed >= 5 && chest.seed < 8) 
        {
            gMin = 45; gMax = 55;
            rUncomThres = 5; rRareThres = 9; rMax = 9;
        }
        else
        {
            gMin = 70; gMax = 80;
            rUncomThres = 0; rRareThres = 7; rMax = 9;
        }
        rMenuTreasure.generate_items(gMin, gMax, 0, 1, 1, rUncomThres, rRareThres, rMax);
        treasureInit = false;
    }
    static SDL_Rect background = {0, 280, 1920, 1225};
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &background);
    ironclad.display(false);
    chest.process();
    if (chest.opened && rMenuTreasure.process()) 
    {
        chest.opened = false;
        game.state_switch(Game::gameStates::map);
    }
    panel.display();
}

Chest::Chest() : Gui(960, 180, 360, 360) {}
void Chest::generate() { seed = rand_int(0, 9); }

void Chest::display() 
{ 
    if (seed >= 0 && seed < 5) 
    {
        if (opened) sprite = "assets/scene/treasure/small_chest_opened.png";
        else sprite = "assets/scene/treasure/small_chest.png";
    }
    else if (seed >= 5 && seed < 8) 
    {
        if (opened) sprite = "assets/scene/treasure/medium_chest_opened.png";
        else sprite = "assets/scene/treasure/medium_chest.png";
    }
    else
    {
        if (opened) sprite = "assets/scene/treasure/large_chest_opened.png";
        else sprite = "assets/scene/treasure/large_chest.png";
    }
    game.render_img(sprite, rect.x, rect.y, rect.w, rect.h, 255, NULL); 
}

void Chest::process()
{
    display();
    if (!opened && !panel.inMenu && detect_click()) opened = true;
}

