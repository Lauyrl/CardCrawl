#pragma once

#include <functional>
#include "../enemies/enemy.h"
#include "../character/character.h"

using namespace std;
// Card IDs enum is defined in character.h
enum cardIntent {
    Attack, Skill, Curse
};

struct CardAttributes 
{
    int cost;
    cardIntent intent;
    bool exhaust;
    const char* sprite;
    function<void(vector<Enemy>&, int)> action;
};
