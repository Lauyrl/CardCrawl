#pragma once

#include <map>
#include <vector>
#include <functional>
#include "../game.h"
#include "../character/character.h"

using namespace std;

enum enemId {
    acid_slime
};

struct enemAttributes 
{
    double hp;
    double atk;
};

extern const map<enemId, const char*> eSpriteMap;

extern const map<enemId, enemAttributes> eAttriMap;


class Enemy;//this file cant know what enemy is
            //but it only needs a partial definition ig
struct possibleActions
{
    int actionValue;
    function<void(Character&, Enemy&)> action;
};
extern const map<enemId, vector<possibleActions>> eActionMap;



