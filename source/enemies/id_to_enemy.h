#pragma once

#include <functional>
#include "../game.h"
#include "../character/character.h"

using namespace std;

enum enemyId {
    acid_slime,
    cultist
};

struct enemAttributes 
{
    double hp;
    double atk;
};

class Enemy; //forward declaration
struct possibleActions
{
    int actionValue;
    function<void(Character&, Enemy&)> action;
};

extern const map<enemyId, vector<possibleActions>> eActionMap;

extern const map<enemyId, const char*> eSpriteMap;

extern const map<enemyId, enemAttributes> eAttriMap;
