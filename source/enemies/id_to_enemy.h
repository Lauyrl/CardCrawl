#pragma once

#include <functional>
#include "../game.h"
#include "../character/character.h"

using namespace std;
//define outside class to avoid clutter
enum enemyId {
    acid_slime,
    cultist
};

class Enemy; //forward declaration
struct possibleActions
{
    int actionValue;
    function<void(Enemy&)> action;
};

struct enemyAttributes 
{
    double hp;
    double atk;
    const char* sprite;
    vector<possibleActions> actions;
};
