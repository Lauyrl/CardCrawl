#include "enemy.h"

void cut(Enemy &enemy) { enemy.deal_damage(6); }
void stab(Enemy &enemy) { enemy.deal_damage(2); }
void tackle(Enemy &enemy) { enemy.deal_damage(12); }
void taunt(Enemy &enemy) { ironclad.statuses[weakness].level += 2; ironclad.statuses[vulnerable].level += 2;}
void weaken(Enemy &enemy) { ironclad.statuses[vulnerable].level++; }
void attack_weaken1(Enemy &enemy) { ironclad.statuses[weakness].level += 2; enemy.deal_damage(7); }
void corrosive_spit(Enemy &enemy) { enemy.deal_damage(8); ironclad.slimedCnt++; }
void shield(Enemy &enemy) { enemy.gain_block(10); }
void gloat(Enemy &enemy) { enemy.statuses[strength].level += 2; }

vector<possibleActions> acid_slime_p1 = {
    {30, 0, 2, {attack1debuff1, corrosive_spit}}, {60, 0, 1, {attack4, tackle}}, {100, 0, 1, {debuff1, weaken}}
};
vector<vector<possibleActions>> acid_slime_p = {acid_slime_p1};
Action acid_slime_alg(Enemy& enemy, int turn) { return rand_get(enemy.attributes.patterns[0]); }

vector<possibleActions> cultist_p1 = {
    {10, 0, 1, attack1, cut}, {100, 0, 1, debuff1, weaken}
};
vector<vector<possibleActions>> cultist_p = {cultist_p1};
Action cultist_alg(Enemy& enemy, int turn) { return rand_get(enemy.attributes.patterns[0]); }

vector<possibleActions> slaver_blue_p1 = {
    {40, 0, 1, attack1debuff1, attack_weaken1}, {100, 0, 1, attack2, stab}
};
vector<vector<possibleActions>> slaver_blue_p = {slaver_blue_p1};
Action slaver_blue_alg(Enemy& enemy, int turn) { return rand_get(enemy.attributes.patterns[0]); }

vector<possibleActions> champ_p1 = {
    {15, 0, 1, {defend1, shield}}, {30, 0, 1, {buff1, gloat}}, {100, 0, 1, {attack3, tackle}}
};
vector<vector<possibleActions>> champ_p = {champ_p1};
Action champ_alg(Enemy& enemy, int turn)
{
    if (turn%8==0) return {debuff1, taunt};
    else return rand_get(enemy.attributes.patterns[0]);
}

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime ,{0, 24, 3, "assets/enemies/acid_slime.png" , acid_slime_p , acid_slime_alg}},
    {cultist    ,{0, 18, 5, "assets/enemies/cultist.png"    , cultist_p    , cultist_alg}},
    {slaver_blue,{1, 50, 7, "assets/enemies/slaver_blue.png", slaver_blue_p, slaver_blue_alg}},
    {champ      ,{2, 100,1, "assets/enemies/champ.png"      , champ_p      , champ_alg}},
};
