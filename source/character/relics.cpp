#include "character.h"

void anchor_ef() {ironclad.block += 10;}
void blood_vial_ef() {ironclad.heal(2);}
const map<relicId, relicAttributes> Relic::relAttriMap = {
    {anchor,     {"assets/relics/anchor.png", anchor_ef}},
    {blood_vial, {"assets/relics/blood_vial.png", blood_vial_ef}}
};


Relic::Relic() : Gui(-25, 30, 100, 100)
{
    id = anchor;
    attributes = relAttriMap.at(id);
}
Relic::Relic(relicId id_) : Gui(60*(ironclad.relicInv.size())-25, 30, 100, 100)
{
    id = id_;
    attributes = relAttriMap.at(id);
}

void Relic::display()
{
    game.render_img(attributes.sprite, rect.x, rect.y, rect.w, rect.h, 200, NULL);
}
