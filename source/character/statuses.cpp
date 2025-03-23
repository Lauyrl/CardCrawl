#include "character.h"

map<statusId, status> Character::statuses = globalStatuses;
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
    if (flexUsed)
    {
        statuses[strength].level -= 2*flexUsed;
        flexUsed = 0;
    }
    cout << "strength: " << statuses[strength].level << endl;
}
