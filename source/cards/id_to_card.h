#pragma once

#include <map>
#include <string>
#include <functional>
#include "../enemies/enemy.h"
#include "../character/character.h"

using namespace std;

// Card IDs enum is defined in character.h
enum cardIntent {Attack, Skill, Curse};

struct CardAttributes
{
    cardIntent intent;
    int energyCost;
};

extern const map<cardIdInv, const char*> cardSpriteMap;

extern const map<cardIdInv, CardAttributes> attriMap;

extern const map<cardIdInv, function<void(Character&, Enemy&)>> actionMap;
