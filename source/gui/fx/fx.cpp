#include "fx.h"

SlashFX::SlashFX() {}
SlashFX::SlashFX(int x_, int y_) : x(x_), y(y_) {}
bool SlashFX::display()
{
    game.render_img("assets/slash_vfx.png", x+190/23.0*t+10, y+220/24.0*t+10, -1.2*t*t+18*t+12, -1.2*t*t+18*t+12, 255, NULL);
    if (t==12) { t = 0; return true; }
    else { t++; return false; }
}

DmgText::DmgText(int dmg_, int x_, int y_) : dmg(dmg_), x(x_), y(y_) {}
bool DmgText::display()
{
    dmgText = Text(30, x-t*0.1, y+0.1*t*t-2*t, 255, 255-t*3, 255-t*3);
    dmgText.render_text("-"+to_string(dmg));
    if (t == 60) { t = 0; return true; }
    else { t++; return false; }
}
