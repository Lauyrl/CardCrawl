#pragma once

#include <functional>
#include "../enemies/enemy.h"
#include "../character/character.h"

using namespace std;

// Card IDs enum is defined in character.h
enum cardIntent {Attack, Skill, Curse};

struct CardAttributes
{
    cardIntent intent;
    int cost;
};

extern const map<cardIdInv, const char*> cSpriteMap;

extern const map<cardIdInv, CardAttributes> cAttriMap;

extern const map<cardIdInv, function<void(Character&, vector<Enemy>&, int)>> cActionMap;
