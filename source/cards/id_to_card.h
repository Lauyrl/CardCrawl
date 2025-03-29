#pragma once

#include <functional>
#include "../enemies/enemy.h"
#include "../character/character.h"

using namespace std;

enum cardId {
    strike, defend, iron_wave, flex, bloodletting, bludgeon, cleave, pom_strike, boomerang,
    bash, clothesline, anger, rage, intimidate, dropkick,
    slimed, burn, the_void
};

enum cardIntent {
    Attack, Skill, Curse
};

struct CardAttributes 
{
    int cost;
    cardIntent intent;
    bool exhaust;
    bool ethereal;
    const char* sprite;
    function<void(vector<Enemy>&, int)> action;
};

