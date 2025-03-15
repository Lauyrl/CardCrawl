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

    int it{0};
    for (auto relic:ironclad.relicInv)
    {
        //if (relic.second)
        {
            // string relicImgDir = "assets/relics/" + relic.first + ".png";
            // game.render_img(relicImgDir.c_str(), 120*it-25, 30, 100, 100, 200, NULL);
            // it++;
        }  
    }
}
