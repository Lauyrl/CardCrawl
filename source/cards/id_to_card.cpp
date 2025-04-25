#include "deck.h"
using namespace std;

void strike_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(16); }//BUFFED FOR DEBUGGING 
void defend_action(vector<Enemy>& enemies, int queried) { ironclad.gain_block(5); }
void flex_action(vector<Enemy>& enemies, int queried) 
{ 
    ironclad.statuses[strength].level += 2; 
    ironclad.flexCnt++;
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
void boomerang_action(vector<Enemy>& enemies, int queried)
{
    int randEnemy = rand_int(0, enemies.size()-1);
    enemies[randEnemy].take_damage(3); enemies[randEnemy].take_damage(3, 10); enemies[randEnemy].take_damage(3, 20);
}
void anger_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(6); deck.discardPile.push_back(Card(anger)); }
void bash_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(8); enemies[queried].statuses[vulnerable].level += 2; }
void clothesline_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(12); enemies[queried].statuses[weakness].level += 2; }
void pom_strike_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(9); deck.drawCards++; }
void rage_action(vector<Enemy>& enemies, int queried) { ironclad.raged = true; }
void intimidate_action(vector<Enemy>& enemies, int queried) { for (auto& enemy:enemies) {enemy.statuses[weakness].level++;} }
void dropkick_action(vector<Enemy>& enemies, int queried) 
{ 
    enemies[queried].take_damage(5); 
    if (enemies[queried].statuses[vulnerable].level>0) { ironclad.energy++; deck.drawCards++; }
}
void inflame_action(vector<Enemy>& enemies, int queried) { ironclad.statuses[strength].level += 2; }
void beserk_action(vector<Enemy>& enemies, int queried) { }

const unordered_map<cardId, CardAttributes> Card::cAttriMap = {
    {strike      ,{1 , Attack, false, false, "assets/cards/strike_r.png"     , strike_action}},
    {iron_wave   ,{1 , Attack, false, false, "assets/cards/iron_wave.png"    , iron_wave_action}},
    {bludgeon    ,{3 , Attack, false, false, "assets/cards/bludgeon.png"     , bludgeon_action}},
    {cleave      ,{1 , Attack, false, false, "assets/cards/cleave.png"       , cleave_action}},
    {boomerang   ,{1 , Attack, false, false, "assets/cards/boomerang.png"    , boomerang_action}},
    {bash        ,{2 , Attack, false, false, "assets/cards/bash.png"         , bash_action}},
    {clothesline ,{2 , Attack, false, false, "assets/cards/clothesline.png"  , clothesline_action}},
    {anger       ,{0 , Attack, false, false, "assets/cards/anger.png"        , anger_action}},
    {pom_strike  ,{1 , Attack, false, false, "assets/cards/pom_strike.png"   , pom_strike_action}},
    {dropkick    ,{1 , Attack, true , false, "assets/cards/dropkick.png"     , dropkick_action}},

    {defend      ,{1 , Skill , false, false, "assets/cards/defend_r.png"     , defend_action}},
    {flex        ,{0 , Skill , false, false, "assets/cards/flex.png"         , flex_action}},
    {bloodletting,{0 , Skill , false, false, "assets/cards/bloodletting.png" , bloodletting_action}},
    {rage        ,{0 , Skill , false, false, "assets/cards/rage.png"         , rage_action}},
    {intimidate  ,{0 , Skill , true , false, "assets/cards/intimidate.png"   , intimidate_action}},

    {slimed      ,{1 , Skill , true , false, "assets/cards/slimed.png"       , [](vector<Enemy>& e, int q){}}},

    {burn        ,{99, Skill , false, false, "assets/cards/burn.png"         , [](vector<Enemy>& e, int q){}}},
    {the_void    ,{99, Skill , false, true , "assets/cards/void.png"         , [](vector<Enemy>& e, int q){}}},

    {inflame     ,{1 , Power , true , false, "assets/cards/inflame.png"      , inflame_action}},
    {beserk      ,{0 , Power , true , false, "assets/cards/beserk.png"       , [](vector<Enemy>& e, int q){}}},
};

