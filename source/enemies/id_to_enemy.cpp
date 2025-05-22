#include "enemy.h"

void cut(Enemy &enemy) { enemy.deal_damage(6); }
void stab(Enemy &enemy) { enemy.deal_damage(2); }
void tackle(Enemy &enemy) { enemy.deal_damage(12); }
void heavy(Enemy &enemy) { enemy.deal_damage(16); }
void execute(Enemy &enemy) { enemy.deal_damage(10); enemy.deal_damage(10, 10); }
void scythe(Enemy &enemy) { enemy.deal_damage(45); }
void maul(Enemy &enemy) { enemy.deal_damage(6); enemy.deal_damage(6, 10); enemy.deal_damage(6, 20); }
void corrosive_spit(Enemy &enemy) { enemy.deal_damage(8); ironclad.slimedCnt++; }
void face_slap(Enemy &enemy) { enemy.deal_damage(12); ironclad.statuses[vulnerable].level += 2; }
void attack_weaken1(Enemy &enemy) { enemy.deal_damage(7); ironclad.statuses[weakness].level += 2; }
void taunt(Enemy &enemy) { ironclad.statuses[weakness].level += 2; ironclad.statuses[vulnerable].level += 2;}
void weaken(Enemy &enemy) { ironclad.statuses[vulnerable].level++; }
void strengthen(Enemy &enemy) { enemy.statuses[strength].level += 2; }
void wrath(Enemy &enemy) { enemy.cleanse(); enemy.statuses[strength].level += 6; }
void defensive_stance(Enemy &enemy) { enemy.gain_block(15); enemy.statuses[metallicize].level += 2; }
void shield(Enemy &enemy) { enemy.gain_block(10); }
void sear(Enemy &enemy) { ironclad.burnCnt++; }
void dread(Enemy &enemy) { ironclad.voidCnt++; }


vector<vector<possibleActions>> acid_slime_p = {
    {{30, 0, 2, {debuff1attack2, corrosive_spit}}, {60, 0, 1, {attack4, tackle}}, {100, 0, 1, {debuff1, weaken}}}
};
Action acid_slime_alg(Enemy& enemy, int turn) { return rand_get(enemy.attributes.patterns[0]); }

vector<vector<possibleActions>> cultist_p = {
    {{10, 0, 1, attack1, cut}, {100, 0, 1, debuff1, weaken}}
};
Action cultist_alg(Enemy& enemy, int turn) { return rand_get(enemy.attributes.patterns[0]); }

vector<vector<possibleActions>> slaver_blue_p = {
    {{40, 0, 1, debuff1attack1, attack_weaken1}, {100, 0, 1, attack2, stab}}
};
Action slaver_blue_alg(Enemy& enemy, int turn) { return rand_get(enemy.attributes.patterns[0]); }

vector<vector<possibleActions>> snake_plant_p = {
    {{65, 0, 2, attack4, heavy}, {100, 0, 1, debuff1, taunt}}
};
Action snake_plant_alg(Enemy& enemy, int turn) 
{ if (turn == 0) { enemy.statuses[malleable].level += 3; } return rand_get(enemy.attributes.patterns[0]); }

vector<vector<possibleActions>> champ_p = {
    {{15, 0, 1, {defendbuff, defensive_stance}}, {30, 0, 1, {buff, strengthen}}, {55, 0, 1, {debuff1attack3, face_slap}}, 
    {100, 0, 1, {attack4, heavy}}}
};
Action champ_alg(Enemy& enemy, int turn)
{
    if (enemy.phase == 0)
    {
        if (enemy.attributes.hp < enemy.maxHealth/2) { enemy.phase++; return {buff, wrath}; }
        else if (turn%8==0) return {debuff1, taunt};
        else return rand_get(enemy.attributes.patterns[0]);
    }
    else 
    {
        if (turn%6==0) return {attack5, execute};
        else return rand_get(enemy.attributes.patterns[0]);
    }
}

vector<vector<possibleActions>> nemesis_p = {
    {{50, 0, 1, {debuff1, sear}}, {50, 0, 1, {attack4, maul}}},
    {{35, 0, 1, {debuff1, sear}}, {70, 0, 2, {attack4, maul}}, {100, 0, 2, {attack5, execute}}}
};
Action nemesis_alg(Enemy& enemy, int turn)
{
    if (turn%4 == 0) enemy.statuses[intangible].level++;
    if (turn == 0) return rand_get(enemy.attributes.patterns[0]);
    else return rand_get(enemy.attributes.patterns[1]);
}

vector<vector<possibleActions>> awakened_p = {
    {{50, 0, 1, {debuff1, sear}}, {25, 0, 1, {attack4, maul}}, {25, 0, 1, {buff, strengthen}}},
    {{35, 0, 1, {debuff1attack4, dread}}, {70, 0, 2, {attack4, maul}}, {100, 0, 2, {attack5, execute}}}
};
Action awakened_alg(Enemy& enemy, int turn)
{
    if (turn<10) return rand_get(enemy.attributes.patterns[0]);
    return rand_get(enemy.attributes.patterns[1]);
}

const map<enemyId, enemyAttributes> Enemy::eAttriMap = {
    {acid_slime ,{0, 24, 3, "assets/enemies/acid_slime.png" , acid_slime_p , acid_slime_alg}},
    {cultist    ,{0, 18, 5, "assets/enemies/cultist.png"    , cultist_p    , cultist_alg}},
    {slaver_blue,{1, 40, 7, "assets/enemies/slaver_blue.png", slaver_blue_p, slaver_blue_alg}},
    {champ      ,{2, 250,1, "assets/enemies/champ.png"      , champ_p      , champ_alg}},
    {nemesis    ,{2, 100,1, "assets/enemies/nemesis.png"    , nemesis_p    , nemesis_alg}},
    {awakened   ,{6, 800,1, "assets/enemies/awakened1.png"  , awakened_p   , awakened_alg}},
    {snake_plant,{2, 70 ,1, "assets/enemies/snake_plant.png", snake_plant_p, snake_plant_alg}},
};
