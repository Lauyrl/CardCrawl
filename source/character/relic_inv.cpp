#include "character.h"

map<relicId, Relic> Character::relicInv;

set<relicId> combatStartRelics = {anchor, blood_vial};
void Character::combat_start_relic()
{
    for (auto& id:combatStartRelics)
    {
        if (relicInv.find(id) != relicInv.end() && relicInv[id].active) 
        {
            if      (id == anchor)     relicInv[id].attributes.effect();
            else if (id == blood_vial) relicInv[id].attributes.effect();
            relicInv[id].active = false;
        }
    }
}

set<relicId> duringTurnRelics = {shuriken, gremlin_horn};
void Character::during_turn_relic(int enemyDeaths)
{
    for (auto& id:duringTurnRelics)
    {
        if (relicInv.find(id) != relicInv.end() && relicInv[id].active) 
        {
            if (id == shuriken && attackCardsUsed >= 3) 
            {
                relicInv[id].attributes.effect();
                relicInv[id].active = false;
            }
            if (id == gremlin_horn && enemyDeaths > 0) { for (int i{0}; i < enemyDeaths; i++) relicInv[id].attributes.effect(); }
        }
    }
}
void Character::during_turn_relic_renew()
{
    for (auto& id:duringTurnRelics)
    {
        if (relicInv.find(id) != relicInv.end() && !relicInv[id].active) relicInv[id].active = true;
    }
}
void Character::combat_start_relic_renew()
{
    for (auto& id:duringTurnRelics)
    {
        if (relicInv.find(id) != relicInv.end() && !relicInv[id].active) relicInv[id].active = true;
    }
}
