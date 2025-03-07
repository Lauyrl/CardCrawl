#include "id_to_enemy.h"

const map<enemyId, const char*> eSpriteMap = {
    {acid_slime, "assets/enemies/acid_slime.png"},
    {cultist, "assets/enemies/cultist2.png"}
};

const map<enemyId, enemAttributes> eAttriMap = {
    {acid_slime, {24, 3}},
    {cultist, {18, 5}}
};

