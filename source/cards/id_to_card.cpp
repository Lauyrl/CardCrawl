#include "card.h"

using namespace std;

void strike_action(vector<Enemy>& enemies, int queried) { enemies[queried].take_damage(16); }
//BUFFED FOR DEBUGGING 
void defend_action(vector<Enemy>& enemies, int queried) { ironclad.gain_block(5); }

void iron_wave_action(vector<Enemy>& enemies, int queried)
{
    ironclad.gain_block(5);
    enemies[queried].take_damage(5);
}

const map<cardIdInv, CardAttributes> Card::cAttriMap = {
    {strike,    {1, Attack, "assets/cards/strike_r.png", strike_action}},
    {defend,    {1, Skill, "assets/cards/defend_r.png", defend_action}},
    {iron_wave, {1, Attack, "assets/cards/iron_wave.png", iron_wave_action}}
};
