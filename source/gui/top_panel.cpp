#include "top_panel.h"

TopPanel::TopPanel() {}
void TopPanel::display()
{
    game.render_img("assets/ui/bar.png",0, 0, SCREEN_WIDTH, 100, 255, NULL);
    game.render_img("assets/ui/panel_heart.png", 10, 8, 40, 40, 255, NULL);
    game.render_img("assets/ui/gold.png", 140, 6, 40, 40, 255, NULL);
    string healthStr = to_string(ironclad.health) + "/" + to_string((int)ironclad.maxHealth);
    healthText.render_text(healthStr);
    goldText.render_text(to_string(ironclad.gold));
    dButton.process();
    inMenu = dButton.active;
    for (auto relic:ironclad.relicInv) relic.second.display();
}

DeckButton::DeckButton() : Gui(1300, 0, 50, 50) {}

void DeckButton::display()
{
    game.render_img("assets/ui/deck.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

void DeckButton::process()
{
    if (active && detect_click()) active = false;
    else if (!active && detect_click()) 
    {
        active = true;
        deck.renew_inventory();
    }
    if (active) deck.display_pile(deck.inventory, 2);
    display();
}
