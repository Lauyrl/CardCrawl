#include "character.h"
//doi ten tu relics_inv.cpp
map<relicId, Relic> Character::relicInv;

set<relicId> combatStartRelics = {anchor, blood_vial};
void Character::combat_start_relic()
{
    if (check_relic_active(anchor)) block += 10;
    if (check_relic_active(blood_vial)) heal(2);
    if (check_relic(tea_set) && !relicInv.at(tea_set).active) { energy += 2; relicInv.at(tea_set).active = true; } //energy += 2 was causing a string bug?
}

set<relicId> duringTurnRelics = {shuriken};
void Character::during_turn_relic()
{
    if (check_relic_active(shuriken) && attackCardsUsed >= 3)
    {
        relicInv.at(shuriken).attributes.effect();
        relicInv.at(shuriken).active = false;
    }
}

void Character::during_turn_relic_renew()
{
    for (auto& id:duringTurnRelics) { if (check_relic(id) && !relicInv.at(id).active) relicInv.at(id).active = true; }
}
