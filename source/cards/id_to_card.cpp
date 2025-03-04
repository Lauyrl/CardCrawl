#include "id_to_card.h"

using namespace std;

const map<cardIdInv, const char*> cSpriteMap = {
    {strike, "assets/cards/strike_r.png"},
    {defend, "assets/cards/defend_r.png"},
    {iron_wave, "assets/cards/iron_wave.png"}
};

const map<cardIdInv, CardAttributes> cAttriMap = {
    {strike, {Attack, 1}},
    {defend, {Skill, 1}},
    {iron_wave, {Attack, 1}}
};

void strike_action(Character& chara, Enemy& enemy)
{
    enemy.take_damage(6);
}

void defend_action(Character& chara, Enemy& enemy)
{
    chara.gain_block(5);
}

void iron_wave_action(Character& chara, Enemy& enemy)
{
    chara.gain_block(5);
    enemy.take_damage(5);
    cout << chara.block << ' ' << endl;
    cout << enemy.attributes.hp << ' ' << endl;
}

const map<cardIdInv, function<void(Character&, Enemy&)>> cActionMap = {
    {strike, strike_action},
    {defend, defend_action},
    {iron_wave, iron_wave_action}
};
