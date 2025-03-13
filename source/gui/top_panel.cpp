#include "top_panel.h"

TopPanel::TopPanel() {}

void TopPanel::display()
{
    game.render_img("assets/ui/bar.png",0, 0, SCREEN_WIDTH, 100, 255, NULL);
    game.render_img("assets/ui/panel_heart.png", 10, 8, 40, 40, 255, NULL);
    string healthStr = to_string(ironclad.health) + "/" + to_string((int)ironclad.maxHealth);
    healthText.render_text(healthStr);
    game.render_img("assets/ui/gold.png", 140, 6, 40, 40, 255, NULL);
    goldText.render_text(to_string(ironclad.gold));
}
