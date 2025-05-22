#include "start_menu.h"

void Game::display_start_menu()
{
    static StartButton stButton;
    render_img("assets/scene/start_menu.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    stButton.process();
}

StartButton::StartButton() : Gui(400, 400, 400, 200) {}

void StartButton::display()
{
    SDL_Rect start{rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(game.renderer, &start);
    startText.render_text("start");
}

void StartButton::process()
{
    display();
    if (detect_click())
    {
        game.state_switch(Game::gameStates::map);
        game.mapGenerated = false;
        ironclad.gold = 0;
        ironclad.maxHealth = 200;
        ironclad.health = ironclad.maxHealth;
        ironclad.relicInv.clear();
        ironclad.renew();
        deck.idInventory  = defaultIdInventory;
        commonCardPool    = commonCardPoolOrigin;
        uncommonCardPool  = uncommonCardPoolOrigin;
        rareCardPool      = rareCardPoolOrigin;
        commonRelicPool   = commonRelicPoolOrigin;
        uncommonRelicPool = uncommonRelicPoolOrigin;
        rareRelicPool     = rareRelicPoolOrigin;
    }
}
