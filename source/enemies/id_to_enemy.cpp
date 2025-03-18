#include "enemy.h"

void eAttack1(Enemy &enemy)
{
    ironclad.take_damge(6);
    //cout << "6 dmg" << endl;
}

void eAttack2(Enemy &enemy)
{
    ironclad.take_damge(2);
}

void weaken(Enemy &enemy)
{
    ironclad.statuses.at(vulnerable).level++;
    cout << ironclad.statuses.at(vulnerable).level << endl;
}

vector<possibleActions> acid_slime_ac = {
    {10, eAttack1},
    {15, eAttack2},
    {100, weaken}
};

vector<possibleActions> cultist_ac = {
    {10, eAttack1},
    {15, eAttack2},
    {100, weaken}
};

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime, {24, 3, "assets/enemies/acid_slime.png", acid_slime_ac}},
    {cultist,    {18, 5, "assets/enemies/cultist2.png", cultist_ac}}
};
