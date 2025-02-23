#include "id_to_card.h"

#include <iostream>
using namespace std;

extern Character chara;
extern Enemy enemy;
const map<cardId, const char*> cardSpriteMap = {
    {strike, "assets/cards/strike_r.png"},
    {defend, "assets/cards/defend_r.png"}
};

const map<cardId, CardAttributes> attriMap = {
    {strike, {Attack, 1}},
    {defend, {Skill, 1}}
};

void strike_action(Character host, Enemy target)
{
    cout << "Strike!" << endl;
}

const map<cardId, function<void(Character, Enemy)>> actionMap = {
    {strike, strike_action}
};







