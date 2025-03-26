#include "enemy.h"

const unordered_map<intentId, IntentAttributes> Intent::intentAttriMap = {
    {attack1,       {"assets/ui/combat/intent/attack1.png", "Deal 0-4 DMG"}},
    {attack2,       {"assets/ui/combat/intent/attack2.png", "Deal 5-9 DMG"}},
    {attack3,       {"assets/ui/combat/intent/attack3.png", "Deal 10-14 DMG"}},
    {attack4,       {"assets/ui/combat/intent/attack4.png", "Deal 15-19 DMG"}},
    {attack5,       {"assets/ui/combat/intent/attack5.png", "Deal 20-24 DMG"}},
    {attack6,       {"assets/ui/combat/intent/attack6.png", "Deal 25-29 DMG"}},
    {attack7,       {"assets/ui/combat/intent/attack7.png", "Deal 30+ DMG"}},
    {debuff1,       {"assets/ui/combat/intent/debuff1.png", "Inflict a debuff"}},
    {debuff2,       {"assets/ui/combat/intent/debuff2.png", "Inflict a Powerful debuff"}},
    {buff1  ,       {"assets/ui/combat/intent/buff1.png"  , "Use a buff"}},
    {defend1,       {"assets/ui/combat/intent/defend.png" , "Intends to block"}},
    {attack1debuff1,{"assets/ui/combat/intent/debuff1attack1.png", "Deal 2-10 DMG and\nInflict a Debuff"}},
};

Intent::Intent() : Gui(0,0,60,60) {}
Intent::Intent(intentId id_) : Gui(0,0,60,60), id(id_) { attributes = intentAttriMap.at(id); }
void Intent::display(int x, int y)
{
    move_rect(x+40, y-40);
    descText = Text(20, rect.x-60, rect.y-70, 255, 220, 220);
    game.render_img(attributes.sprite, rect.x, rect.y, rect.w, rect.h, 255, NULL);
    if (detect_cursor_hover()) display_desc();
}
void Intent::display_desc()
{
    game.render_img("assets/ui/popup.png", rect.x-180, rect.y-130, 400, 180, 220, NULL);
    descText.render_text(attributes.desc);
}
