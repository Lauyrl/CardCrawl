#include "enemy.h"

const map<enemyId, const char*> Enemy::eSpriteMap = {
    {acid_slime, "assets/enemies/acid_slime.png"},
    {cultist, "assets/enemies/cultist2.png"}
};

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime, {24, 3}},
    {cultist, {18, 5}}
};


void eAttack1(Character &chara, Enemy &enemy)
{
    chara.take_damge(6);
}

void eAttack2(Character &chara, Enemy &enemy)
{
    chara.take_damge(2);
}

vector<possibleActions> acid_slime_ac = {
    {50,  eAttack1},
    {100, eAttack2}
};

vector<possibleActions> cultist_ac = {
    {60,  eAttack1},
    {100, eAttack2}
};

const map<enemyId, vector<possibleActions>> Enemy::eActionMap = {
    {acid_slime, acid_slime_ac},
    {cultist, cultist_ac}
};
