#include "enemy.h"

void attack1(Enemy &enemy) { enemy.deal_damage(6); }

void attack2(Enemy &enemy) { enemy.deal_damage(2); }

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
    {30, corrosive_spit, "assets/ui/combat/intent/debuff1attack1.png"},
    {100, weaken, "assets/ui/combat/intent/debuff1.png"}
};

vector<possibleActions> cultist_ac = {
    {10, attack1, "assets/ui/combat/intent/attack1.png"},
    {100, weaken, "assets/ui/combat/intent/debuff1.png"}
};

vector<possibleActions> slaver_blue_ac = {
    {40, attack_weaken1, "assets/ui/combat/intent/debuff1attack1.png"},
    {100, attack2, "assets/ui/combat/intent/attack2.png"}
};

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime, {24, 3, "assets/enemies/acid_slime.png" , acid_slime_ac}},
    {cultist,    {18, 5, "assets/enemies/cultist.png"    , cultist_ac}},
    {slaver_blue,{50, 7, "assets/enemies/slaver_blue.png", slaver_blue_ac}}
};
