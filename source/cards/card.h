#pragma once

#include "../game.h"
#include "../gui/gui.h"
#include "id_to_card.h" //includes Enemy and Character

using namespace std;

const int NULL_CARD = -1;
const int CARD_POS_X_DEFAULT = 300;
const int STEP_INCREMENT = 190;
const int CARD_POS_Y = 675;
const int CHARACTER_TARGET = 0;

class Card : public Gui
{
    public:
        Card();
        Card(cardIdInv id_, int initPos); // Card IDs enum is defined in character.h
        void display();
        void highlight();
        void activate(Character &chara, Enemy &enemy);
        int query_targetE(vector<Enemy> stageEnemies);
        int query_targetC(Character chara);

        int pos;
        cardIdInv id;
        CardAttributes attributes;
        bool selected{false};
};
