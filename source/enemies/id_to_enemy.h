#pragma once

#include <functional>
#include "intent.h"

using namespace std;
//define outside class to avoid clutter
enum enemyId {
    acid_slime, cultist, slaver_blue, snake_plant,
    champ, nemesis,
    awakened
};

class Enemy; //forward declaration
struct Action
{
    intentId intentId;
    function<void(Enemy&)> action;
};

struct possibleActions
{
    int value;
    int usage;
    int usageMax;
    Action actionObj;
};

struct enemyAttributes 
{
    int size;
    double hp;
    double atk;
    const char* sprite;
    vector<vector<possibleActions>> patterns;
    function<Action(Enemy&,int)> alg;
};
