#include "enemy.h"

const unordered_map<intentId, IntentAttributes> Intent::intentAttriMap = {
    {attack1,       {"assets/ui/combat/intent/attack1.png", "Deal 2-10 DMG"}},
    {attack2,       {"assets/ui/combat/intent/attack2.png", "Deal 10-20 DMG"}},
    {debuff1,       {"assets/ui/combat/intent/debuff1.png", "Inflict a debuff"}},
    {attack1debuff1,{"assets/ui/combat/intent/debuff1attack1.png", "Deal 2-10 DMG and\nInflict a Debuff"}},
};
Intent::Intent() : Gui(0,0,0,0) {}
Intent::Intent(intentId id_, int x_, int y_) : Gui(x_+40,y_-40,60,60), id(id_) { attributes = intentAttriMap.at(id); descText = Text(20, rect.x-60, rect.y-70, 255, 220, 220); }
void Intent::display()
{
    game.render_img(attributes.sprite, rect.x, rect.y, rect.w, rect.h, 255, NULL);
    if (detect_cursor_hover()) display_desc();
}
void Intent::display_desc()
{
    game.render_img("assets/ui/popup.png", rect.x-180, rect.y-130, 400, 180, 220, NULL);
    descText.render_text(attributes.desc);
}
