#include <iostream>
#include "id_to_card.h"

using namespace std;

const map<cardIdInv, const char*> cSpriteMap = {
    {strike, "assets/cards/strike_r.png"},
    {defend, "assets/cards/defend_r.png"}
};

const map<cardIdInv, CardAttributes> cAttriMap = {
    {strike, {Attack, 1}},
    {defend, {Skill, 1}}
};

void strike_action(Character& chara, Enemy& target)
{
    target.take_damage(10);
    cout << target.attributes.hp << ' ' << endl;
}

void defend_action(Character& chara, Enemy& enem)
{
    chara.gain_block(5);
    cout << chara.block << ' ' << endl;
}

const map<cardIdInv, function<void(Character&, Enemy&)>> cActionMap = {
    {strike, strike_action},
    {defend, defend_action}
};
