#pragma once

#include <string>
#include "../gui/gui.h"
#include "id_to_card.h" //includes Enemy and Character

using namespace std;

const int NULL_CARD = -1;
const int START_LOC_X = 300;
const int STEP_INCREMENT = 190;
const int DEFAULT_Y = 675;

class Card : public Gui
{
    public:
        Card(cardIdInv id_, int cardPos); // Card IDs enum is defined in character.h
        void card_display();
        void highlight();
        void reposition_in_deck(int rePos);
        void activate(Character &chara, Enemy &enemy);
        int query_targetE(vector<Enemy> stage_enemies);
        int query_targetC(Character chara);

        int pos;
        cardIdInv id;
        CardAttributes attributes;
        bool selected{false};
};
