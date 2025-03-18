#include "character.h"

map<statusId, status> Character::statuses = {
    {weakness,   {0, 0.25, "assets/ui/combat/status/weak.png"}},
    {strength,   {0, 1, "assets/ui/combat/status/strength.png"}},
    {vulnerable, {0, 0.5, "assets/ui/combat/status/vulnerable.png"}},
    {thorns,     {0, 1, "assets/ui/combat/status/thorns.png"}}
};

set<statusId> decrementableStatuses = {
    weakness, vulnerable
};

void Character::decrement_statuses()
{
    for (auto& status:statuses)
    {
        if (decrementableStatuses.find(status.first) != decrementableStatuses.end() && status.second.level > 0)
            status.second.level--;
    }
    if (flexEndTurnEffect)
    {
        statuses[strength].level -= 2*flexEndTurnEffect;
        flexEndTurnEffect = 0;
    }
    cout << "strength: " << statuses[strength].level << endl;
}
