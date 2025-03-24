#pragma once

#include <functional>
#include "intent.h"

using namespace std;
//define outside class to avoid clutter
enum enemyId {
    acid_slime, cultist, slaver_blue
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
    double hp;
    double atk;
    const char* sprite;
    vector<possibleActions> actions;
};
