#include "enemy.h"

//Defined outside of Enemy to avoid clutter
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

const map<enemyId, vector<possibleActions>> eActionMap = {
    {acid_slime, acid_slime_ac},
    {cultist, cultist_ac}
};
