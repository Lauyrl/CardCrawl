#pragma once

#include "../../game.h"
#include "../../gui/top_panel.h"

struct CardItem
{
    int cost;
    Card card;
    Text costText = Text(1,1,1,1,1,1);
    CardItem(int cost_, Card card_)
    {
        cost = cost_;
        card = card_;
    }
};
struct RelicItem
{
    int cost;
    Relic relic;
    Text costText = Text(1,1,1,1,1,1);
    RelicItem(int cost_, Relic relic_)
    {
        cost = cost_;
        relic = relic_;
    }
};
class Shop
{
    public: 
        Shop();
        void generate_items();
        void display_items(); 
        void purchase_process();
        void process();     
        vector<CardItem> shopCards;
        vector<RelicItem> shopRelics;
        static vector<cardIdInv> cardIds;
        static vector<relicId> relicIds;
};

class ReturnButton : public Gui
{
    public:
        ReturnButton();
        void display();
        void process();
};
