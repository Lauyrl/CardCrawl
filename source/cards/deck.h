#pragma once

#include <vector>
#include "card.h" //already includes Enemy and Character

const int DECK_REC_START_X = 180;
const int DECK_REC_START_Y = 420;
const int DECK_REC_WIDTH  = 980;
const int DECK_REC_HEIGHT = 300;
const int DECK_MAX_SIZE = 5;

class Deck
{
    public:
        Deck(int size_);
        void set_up(Character character);
        void add_card(Card card);
        void remove_card();
        void reformat_deck();
        void activate_card_process(Character &chara, vector<Enemy> &stage_enemies);
        void deck_iterate(int current, Character &chara, vector<Enemy> &stage_enemies);
        void select_card(int toSelect, int charEnergy);

        static vector<Card> hand;
        static vector<Card> drawPile;
        static vector<Card> discardPile;
        static size_t size;
        static int selectedCardIndex;   
        int toDiscard;
};
