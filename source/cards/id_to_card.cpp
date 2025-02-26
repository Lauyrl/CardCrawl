#include <iostream>
#include "id_to_card.h"

using namespace std;

const map<cardIdInv, const char*> cardSpriteMap = {
    {strike, "assets/cards/strike_r.png"},
    {defend, "assets/cards/defend_r.png"}
};

const map<cardIdInv, CardAttributes> attriMap = {
    {strike, {Attack, 1}},
    {defend, {Skill, 1}}
};

void strike_action(Character& host, Enemy& target)
{
    cout << "Address of target: " << &target << endl;
    target.attributes.hp -= 6;
    cout << target.attributes.hp << ' ' << endl;
}

const map<cardIdInv, function<void(Character&, Enemy&)>> actionMap = {
    {strike, strike_action}
};







