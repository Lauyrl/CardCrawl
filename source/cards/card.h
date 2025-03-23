#pragma once

#include "../game.h"
#include "../gui/gui.h"
#include "id_to_card.h" //includes Enemy and Character

using namespace std;

const int NULL_CARD = -1;
const int CARD_POS_X_DEFAULT = 300;
const int STEP_INCREMENT = 140;
const int CARD_POS_Y = 675;
const int CHARACTER_TARGET = 0;

class Card : public Gui
{
    public:
        Card();
        Card(cardId id_, int initPos); // Card IDs enum is defined in character.h
        void display_in_hand(int quantity);
        void display_copy(int x, int y, bool move = false, bool highlight = true);
        bool highlight();
        void activate(vector<Enemy>& stageEnemies, int queried);
        int query_targetE(vector<Enemy> stageEnemies);
        int query_targetC();

        int pos{0};
        cardId id{strike};
        CardAttributes attributes;
        bool selected{false};

        static const unordered_map<cardId, CardAttributes> cAttriMap;
};
