#include "id_to_enemy.h"

const map<enemId, const char*> eSpriteMap = {
    {acid_slime, "assets/enemies/acid_slime.png"}
};

const map<enemId, enemAttributes> eAttriMap = {
    {acid_slime, {24, 3}}
};
