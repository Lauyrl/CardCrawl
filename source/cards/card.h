#pragma once

#include <string>
#include "../gui/gui.h"
#include "id_to_card.h" //includes Enemy and Character

using namespace std;

const int NULL_CARD = -1;
const int START_LOC_X = 180;
const int STEP_INCREMENT = 180;
const int DEFAULT_Y = 490;

class Card : public Gui
{
    public:
        Card(cardIdInv id, int cardPos); // Card IDs enum is defined in character.h
        void card_display(cardIdInv id, int pos);
        void reposition_in_deck(int rePos);
        void activate(Character &chara, Enemy &enemy);
        int query_targetE(vector<Enemy> stage_enemies);
        int query_targetC(Character chara);

        int pos;
        cardIdInv id;
        CardAttributes attributes;
    private:
};

Card card_init(cardIdInv id, int cardPos);
