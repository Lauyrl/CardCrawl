#pragma once

#include "card.h" //already includes Enemy and Character

const int DECK_MAX_SIZE = 5;
const int DP_TEXT  = 0;
const int DC_TEXT  = 1;
const int INV_TEXT = 2;

class Deck
{
    public:
        Deck(int size_);
        void renew();
        void renew_inventory();
        void set_up_piles();
        void refill_draw_pile();
        void display_pile(vector<Card>& pile, int textType, bool move = false, bool highlight = false);
        void build_hand();
        void reformat_hand();
        void discard_hand();
        void renew_hand();
        void hand_process(bool inMenu, vector<Enemy>& stageEnemies);
        void draw_card();
        void discard_used();
        void select_card(int toSelect);
        void query_and_activate_card_process(vector<Enemy> &stageEnemies);
        void interact_card(int current, vector<Enemy> &stageEnemies);
        int interact_cards_event(bool inMenu, int textType);

        vector<Card> hand;
        vector<Card> drawPile;
        vector<Card> discardPile;
        vector<Card> exaustPile;
        vector<Card> inventory;
        static size_t maxSize;
        int highlightedIdx{NULL_CARD};
        int selectedIdx{NULL_CARD}; 
        int usedIdx{NULL_CARD};
        Text pileLabel = Text(30, 400, 50, 255, 255, 255);

        int scrollVal{1};
};

extern Deck deck;
