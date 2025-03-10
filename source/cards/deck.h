#pragma once

#include "card.h" //already includes Enemy and Character

const int DECK_POS_X = 180;
const int DECK_POS_Y = 420;
const int DECK_WIDTH  = 980;
const int DECK_HEIGHT = 300;
const int DECK_MAX_SIZE = 5;
const int DP_TEXT = 0;
const int DC_TEXT = 1;

class Deck
{
    public:
        Deck(int size_);
        void set_up_dp(Character chara);
        void show_pile(vector<Card>& pile, int textType);
        void build_hand();
        void reformat_hand();
        void discard_hand();
        void renew_hand();
        void add_card(vector<Card> &pile, int idx, Card card);
        void discard_card();
        void select_card(int toSelect, int charaEnergy);
        void activate_card_process(Character &chara, vector<Enemy> &stageEnemies);
        void interact_cards(int current, Character &chara, vector<Enemy> &stageEnemies);

        vector<Card> hand;
        vector<Card> drawPile;
        vector<Card> discardPile;
        static size_t maxSize;
        int selectedCardIdx{NULL_CARD};   
        int toDiscard{NULL_CARD};
        Text pileLabel = Text(30, 400, 30, 255, 255, 255);
};
