#pragma once

#include <map>
#include "../game.h"

using namespace std;

enum enemId {
    acid_slime
};

struct enemAttributes 
{
    int hp;
    int atk;
};

extern const map<enemId, const char*> eSpriteMap;

extern const map<enemId, enemAttributes> eAttriMap;



