#include "character.h"
//doi ten tu relics_inv.cpp
map<relicId, Relic> Character::relicInv;

set<relicId> combatStartRelics = {anchor, blood_vial};
void Character::combat_start_relic()
{
    for (auto& id:combatStartRelics)
    {
        if (relicInv.find(id) != relicInv.end() && relicInv.at(id).active) 
        {
            if      (id == anchor)     relicInv.at(id).attributes.effect();
            else if (id == blood_vial) relicInv.at(id).attributes.effect();
            relicInv.at(id).active = false;
        }
    }
}

set<relicId> duringTurnRelics = {shuriken};
void Character::during_turn_relic()
{
    for (auto& id:duringTurnRelics)
    {
        if (relicInv.find(id) != relicInv.end() && relicInv.at(id).active) 
        {
            if (id == shuriken && attackCardsUsed >= 3) 
            {
                relicInv.at(id).attributes.effect();
                relicInv.at(id).active = false;
            }
        }
    }
}


void Character::during_turn_relic_renew()
{
    for (auto& id:duringTurnRelics)
    {
        if (relicInv.find(id) != relicInv.end() && !relicInv.at(id).active) relicInv.at(id).active = true;
    }
}
void Character::combat_start_relic_renew()
{
    for (auto& id:duringTurnRelics)
    {
        if (relicInv.find(id) != relicInv.end() && !relicInv.at(id).active) relicInv.at(id).active = true;
    }
}
