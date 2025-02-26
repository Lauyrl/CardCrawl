#pragma once

#include <vector>
#include "card.h"
#include "../character/character.h"
#include "../enemies/enemy.h"

const int DECK_REC_START_X = 180;
const int DECK_REC_START_Y = 420;
const int DECK_REC_WIDTH = 980;
const int DECK_REC_HEIGHT = 300;
const int DECK_MAX_SIZE = 5;

class Deck : public Gui
{
    public:
        Deck(int size_);
        void set_up(Character character);
        void add_card(Card card);
        void remove_card(int index);  
        void deck_iterate(int current, Character &chara, vector<Enemy> &stage_enemies, int numOfEnemies);
        void assess_card(int assessed, Character &chara, vector<Enemy> &stage_enemies);

        static std::vector<Card> hand;
        static size_t size;
        static int selectedCardIndex;   
        int toRemove;
};

Deck deck_init(int size_);
void reformat_deck(std::vector<Card> &hand_, size_t newSize);

