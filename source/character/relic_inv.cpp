#include "character.h"

vector<Relic> Character::relicInv;

set<relicId> combatStartRelics = {anchor, blood_vial};
void Character::combat_start_relic()
{
    for (auto& relic:relicInv)
    {
        if (combatStartRelics.find(relic.id) != combatStartRelics.end() && relic.active)
        {
            if      (relic.id == anchor)     relic.attributes.effect();
            else if (relic.id == blood_vial) relic.attributes.effect();
            relic.active = false;
        }
    }
}

void Character::combat_start_relic_renew()
{
    for (const auto& relic:relicInv)
    {
        if (combatStartRelics.find(relic.id) != combatStartRelics.end() && relic.active)
            relicInv[relic.id].active = true;
    }
}
