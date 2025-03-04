#pragma once

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
        void set_up_draw_pile(Character chara);
        void build_hand();
        void clear_hand();
        void add_card(vector<Card> &pile, int idx, Card card);
        void discard_card();
        void reformat();
        void activate_card_process(Character &chara, vector<Enemy> &stageEnemies);
        void iterate(int current, Character &chara, vector<Enemy> &stageEnemies);
        void select_card(int toSelect, int charaEnergy);

        static vector<Card> hand;
        static vector<Card> drawPile;
        static vector<Card> discardPile;
        static size_t maxSize;
        static int selectedCardIdx;   
        int toDiscard;
};
