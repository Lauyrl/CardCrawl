#pragma once

#include <string>
#include "../gui/gui.h"
#include "id_to_card.h"

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
        void object_loop(int current, int &selectedCard, int &toRemove, Character &chara, Enemy &enemy);
        void assess_card(int assessed, int &selectedCard, int &toRemove, Character &chara, Enemy &enemy);
        void activate(Character &chara, Enemy &enemy);
        void reposition_in_deck(int rePos);

        int pos;
        cardIdInv id;
        CardAttributes attributes;
    private:
};

Card card_init(cardIdInv id, int cardPos);
