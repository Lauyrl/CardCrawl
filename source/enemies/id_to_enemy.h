#pragma once

#include <map>
#include <vector>
#include <functional>
#include "../game.h"
#include "../character/character.h"

using namespace std;

enum enemyId {
    acid_slime
};

struct enemAttributes 
{
    double hp;
    double atk;
};

extern const map<enemyId, const char*> eSpriteMap;

extern const map<enemyId, enemAttributes> eAttriMap;


class Enemy;//this file cant include enemy.h
            //but it only needs a partial definition ig
struct possibleActions
{
    int actionValue;
    function<void(Character&, Enemy&)> action;
};
extern const map<enemyId, vector<possibleActions>> eActionMap;



