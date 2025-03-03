#pragma once

#include <vector>
#include "card.h" //already includes Enemy and Character

const int DECK_POS_X = 180;
const int DECK_POS_Y = 420;
const int DECK_WIDTH  = 980;
const int DECK_HEIGHT = 300;
const int DECK_MAX_SIZE = 5;

class Deck
{
    public:
        Deck(int size_);
        void set_up(Character chara);
        void add_card(Card card);
        void remove_card();
        void reformat();
        void activate_card_process(Character &chara, vector<Enemy> &stageEnemies);
        void iterate(int current, Character &chara, vector<Enemy> &stageEnemies);
        void select_card(int toSelect, int charaEnergy);

        static vector<Card> hand;
        static vector<Card> drawPile;
        static vector<Card> discardPile;
        static size_t size;
        static int selectedCardIdx;   
        int toDiscard;
};
