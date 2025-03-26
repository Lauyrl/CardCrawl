#include "../cards/deck.h"

void circlet_ef()     { cout << "circlet." << endl; }
void shuriken_ef()    { ironclad.statuses[strength].level++; }
void gremlin_horn_ef(){ ironclad.energy++; deck.draw_card(); }
const unordered_map<relicId, relicAttributes> Relic::relAttriMap = {
    {circlet      ,{"circlet"      , circlet_ef      ,"Appears once a pool is empty"}},
    {anchor       ,{"anchor"       , [](){}          ,"Start combat with 10 block"}},
    {blood_vial   ,{"blood_vial"   , [](){}          ,"Heal 2HP at combat start"}},
    {shuriken     ,{"shuriken"     , shuriken_ef     ,"After playing 3 Attack cards in\nONE turn, gain 1 Strength"}},
    {gremlin_horn ,{"gremlin_horn" , gremlin_horn_ef ,"When an enemy dies, gain 1 energy,\ndraw 1 card"}},
    {singing_bowl ,{"singing_bowl" , [](){}          ,"???"}},
    {bronze_scales,{"bronze_scales", [](){}          ,"When attacked, deal 3DMG to the\n attacker"}},
    {tea_set      ,{"tea_set"      , [](){}          ,"After entering a rest site, start\nthe next combat with +2ENERGY"}},
};


Relic::Relic() : Gui(-25, 30, 100, 100) {}
Relic::Relic(relicId id_) : Gui(60*((int)ironclad.relicInv.size())-25, 30, 60, 100)
{
    id = id_;
    attributes = relAttriMap.at(id);
}
void Relic::display(int where, bool info) 
{ 
    game.render_img(("assets/relics/"+attributes.name+".png").c_str(), rect.x-25, rect.y, rect.w+40, rect.h, 200, NULL); 
    if (info && detect_cursor_hover()) display_info(where);
}
void Relic::display_info(int where) 
{ 
    if (where == DISPLAY_FULL)
    {
        game.render_img("assets/ui/popup.png", rect.x-160, rect.y-10, 700, 300, 220, NULL);
        nameText = Text(24, rect.x+35, rect.y+80 , 255, 255, 190);
        descText = Text(20, rect.x+35, rect.y+110, 255, 255, 255);
        nameText.render_text(attributes.name);
        descText.render_text(attributes.desc);
    }
    else 
    {
        game.render_img("assets/ui/popup.png", rect.x-560, rect.y-78, 700, 300, 220, NULL);
        descText = Text(22, rect.x-360, rect.y+15, 255, 255, 255);
        descText.render_text(attributes.desc);
    }
}
