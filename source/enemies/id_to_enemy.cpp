#include "enemy.h"

void eAttack1(Enemy &enemy)
{
    ironclad.take_damge(6);
    //cout << "6 dmg" << endl;
}

void eAttack2(Enemy &enemy) { ironclad.take_damge(2); }

void weaken(Enemy &enemy)
{
    ironclad.statuses.at(vulnerable).level++;
    cout << ironclad.statuses.at(vulnerable).level << endl;
}

vector<possibleActions> acid_slime_ac = {
    {10, eAttack1, "assets/ui/combat/intent/attack1.png"},
    {50, eAttack2, "assets/ui/combat/intent/attack2.png"},
    {100, weaken,  "assets/ui/combat/intent/debuff1.png"}
};

vector<possibleActions> cultist_ac = {
    {10, eAttack1, "assets/ui/combat/intent/attack1.png"},
    {50, eAttack2, "assets/ui/combat/intent/attack2.png"},
    {100, weaken,  "assets/ui/combat/intent/debuff1.png"}
};

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime, {24, 3, "assets/enemies/acid_slime.png", acid_slime_ac}},
    {cultist,    {18, 5, "assets/enemies/cultist.png"  , cultist_ac}}
};
