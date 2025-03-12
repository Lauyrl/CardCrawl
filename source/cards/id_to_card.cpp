#include "card.h"

using namespace std;

const map<cardIdInv, const char*> Card::cSpriteMap = {
    {strike, "assets/cards/strike_r.png"},
    {defend, "assets/cards/defend_r.png"},
    {iron_wave, "assets/cards/iron_wave.png"}
};

const map<cardIdInv, CardAttributes> Card::cAttriMap = {
    {strike, {Attack, 1}},
    {defend, {Skill, 1}},
    {iron_wave, {Attack, 1}}
};


void strike_action(vector<Enemy>& enemies, int queried)
{
    enemies[queried].take_damage(16); //BUFFED FOR DEBUGGING
}

void defend_action(vector<Enemy>& enemies, int queried)
{
    ironclad.gain_block(5);
}

void iron_wave_action(vector<Enemy>& enemies, int queried)
{
    ironclad.gain_block(5);
    enemies[queried].take_damage(5);
}

const map<cardIdInv, function<void(vector<Enemy>&, int)>> Card::cActionMap = {
    {strike, strike_action},
    {defend, defend_action},
    {iron_wave, iron_wave_action}
};
// check for invalid indices while working with queried
