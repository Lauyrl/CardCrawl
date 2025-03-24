#include "enemy.h"

void cut(Enemy &enemy) { enemy.deal_damage(6); }

void stab(Enemy &enemy) { enemy.deal_damage(2); }

void weaken(Enemy &enemy)
{
    ironclad.statuses[vulnerable].level++;
    cout << ironclad.statuses[vulnerable].level << endl;
}

void attack_weaken1(Enemy &enemy) 
{
    ironclad.statuses[weakness].level += 2;
    enemy.deal_damage(7);
}

void corrosive_spit(Enemy &enemy)
{
    enemy.deal_damage(11);
    ironclad.slimedCnt++;
}

vector<possibleActions> acid_slime_ac = {
    {30 , corrosive_spit, attack1debuff1},
    {100, weaken, debuff1}
};

vector<possibleActions> cultist_ac = {
    {10, cut, attack1},
    {100, weaken, debuff1}
};

vector<possibleActions> slaver_blue_ac = {
    {40 , attack_weaken1, attack1debuff1},
    {100, stab, attack2}
};

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime, {24, 3, "assets/enemies/acid_slime.png" , acid_slime_ac}},
    {cultist,    {18, 5, "assets/enemies/cultist.png"    , cultist_ac}},
    {slaver_blue,{50, 7, "assets/enemies/slaver_blue.png", slaver_blue_ac}}
};
