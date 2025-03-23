#include "../cards/deck.h"

void anchor_ef()      { ironclad.block += 10; }
void blood_vial_ef()  { ironclad.heal(2); }
void circlet_ef()     { cout << "circlet." << endl; }
void shuriken_ef()    { ironclad.statuses[strength].level++; }
void gremlin_horn_ef(){ ironclad.energy++; deck.draw_card(); }
const unordered_map<relicId, relicAttributes> Relic::relAttriMap = {
    {circlet,      {"assets/relics/circlet.png", circlet_ef}},
    {anchor,       {"assets/relics/anchor.png", anchor_ef}},
    {blood_vial,   {"assets/relics/blood_vial.png", blood_vial_ef}},
    {shuriken,     {"assets/relics/shuriken.png", shuriken_ef}},
    {gremlin_horn, {"assets/relics/gremlin_horn.png", gremlin_horn_ef}},
    {singing_bowl, {"assets/relics/singing_bowl.png", [](){}}},
    {bronze_scales,{"assets/relics/bronze_scales.png", [](){}}},
    {tea_set,      {"assets/relics/tea_set.png", [](){}}},
};


Relic::Relic() : Gui(-25, 30, 100, 100) {}
Relic::Relic(relicId id_) : Gui(60*((int)ironclad.relicInv.size())-25, 30, 100, 100)
{
    id = id_;
    attributes = relAttriMap.at(id);
}
void Relic::display() { game.render_img(attributes.sprite, rect.x, rect.y, rect.w, rect.h, 200, NULL); }
