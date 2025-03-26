#pragma once

#include <functional>
#include "intent.h"

using namespace std;
//define outside class to avoid clutter
enum enemyId {
    acid_slime, cultist, slaver_blue, champ
};

class Enemy; //forward declaration
struct possibleActions
{
    int actionValue;
    function<void(Enemy&)> action;
    intentId intentId;
};

struct enemyAttributes 
{
    int size;
    double hp;
    double atk;
    const char* sprite;
    vector<possibleActions> actions;
};
