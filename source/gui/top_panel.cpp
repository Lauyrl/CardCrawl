#include "top_panel.h"

TopPanel::TopPanel()
{
    chara = ironclad;
}

void TopPanel::display()
{
    game.render_img("assets/ui/bar.png",0, 0, SCREEN_WIDTH, 30, NULL);
    game.render_img("assets/ui/gold.png", 120, 10, 15, 15, 255, NULL);
    game.render_img("assets/ui/panel_heart.png", 20, 10, 15, 15, 255, NULL);
}
