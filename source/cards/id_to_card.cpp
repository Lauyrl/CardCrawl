#include "card.h"
using namespace std;

void strike_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(16); }//BUFFED FOR DEBUGGING 
void defend_action(vector<Enemy>& enemies, int queried) { ironclad.gain_block(5); }
void flex_action(vector<Enemy>& enemies, int queried) 
{ 
    ironclad.statuses[strength].level += 2; 
    ironclad.flexUsed++;
} 
void iron_wave_action(vector<Enemy>& enemies, int queried)
{
    ironclad.gain_block(5);
    enemies[queried].take_damage(5);
}
void bloodletting_action(vector<Enemy>& enemies, int queried)
{
    ironclad.energy += 2;
    ironclad.take_damage(3);
}
void bludgeon_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(32); }
void cleave_action(vector<Enemy>& enemies, int queried)
{
    for (auto& enemy:enemies) enemy.take_damage(8);
}
void sword_boomerang_action(vector<Enemy>& enemies, int queried)
{
    int randEnemy = rand_int(0, enemies.size()-1);
    enemies[randEnemy].take_damage(3); enemies[randEnemy].take_damage(3); enemies[randEnemy].take_damage(3);
}
const unordered_map<cardId, CardAttributes> Card::cAttriMap = {
    {strike,      {1, Attack, false, "assets/cards/strike_r.png"    , strike_action}},
    {defend,      {1, Skill , false, "assets/cards/defend_r.png"    , defend_action}},
    {iron_wave,   {1, Attack, false, "assets/cards/iron_wave.png"   , iron_wave_action}},
    {flex,        {0, Skill , false, "assets/cards/flex.png"        , flex_action}},
    {bloodletting,{0, Skill , false, "assets/cards/bloodletting.png", bloodletting_action}},
    {bludgeon,    {3, Attack, false, "assets/cards/bludgeon.png"    , bludgeon_action}},
    {slimed,      {1, Skill , true , "assets/cards/slimed.png"      , [](vector<Enemy>& enemies, int queried){}}},
    {cleave,      {1, Attack, false, "assets/cards/cleave.png"      , cleave_action}},
    {sword_boomerang, {1, Attack, false, "assets/cards/sword_boomerang.png", sword_boomerang_action}}
};
