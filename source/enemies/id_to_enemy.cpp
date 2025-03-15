#include "enemy.h"

void eAttack1(Enemy &enemy)
{
    ironclad.take_damge(6);
    cout << "6 dmg" << endl;
}

void eAttack2(Enemy &enemy)
{
    ironclad.take_damge(2);
}

vector<possibleActions> acid_slime_ac = {
    {50,  eAttack1},
    {100, eAttack2}
};

vector<possibleActions> cultist_ac = {
    {60,  eAttack1},
    {100, eAttack2}
};

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime, {24, 3, "assets/enemies/acid_slime.png", acid_slime_ac}},
    {cultist,    {18, 5, "assets/enemies/cultist2.png", cultist_ac}}
};
