#include "enemy.h"

//Defined outside of Enemy to avoid clutter
void eAttack1(Character &chara, Enemy &enemy)
{
    chara.take_damge(6);
    cout << chara.health << ' ' << chara.block << ' ' << endl;
}

void eAttack2(Character &chara, Enemy &enemy)
{
    chara.take_damge(2);
    cout << chara.health << ' ' << chara.block << ' ' << endl;
}

vector<possibleActions> acid_slime_A = {
    {50,  eAttack1},
    {100, eAttack2}
};

const map<enemyId, vector<possibleActions>> eActionMap = {
    {acid_slime, acid_slime_A}
};
