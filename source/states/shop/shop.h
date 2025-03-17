#pragma once

#include "../../game.h"
#include "../../pools/pools.h"

struct CardItem
{
    int cost;
    Card card;
    Text costText = Text(0,0,0,0,0,0);
    vector<cardIdInv>* pool;
    CardItem() {}
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
    Text costText = Text(0,0,0,0,0,0);
    set<relicId>* pool;
    RelicItem() {}
    RelicItem(int cost_, Relic relic_)
    {
        cost = cost_;
        relic = relic_;
    }
};

class RemovalService : public Gui
{
    public:
        RemovalService();
        void display();
        void process();
        bool used{false};
        bool active{false};
        static int cost;
        Text costText = Text(20, rect.x+94, rect.y+280, 255, 255, 255);
};
class Shop
{
    public: 
        Shop();
        void generate_items();
        void display_items(); 
        void purchase_process();
        void process();     
        vector<CardItem>  shopCards;
        vector<RelicItem> shopRelics;
        RemovalService rsButton;
};

class ReturnButton : public Gui
{
    public:
        ReturnButton();
        void display();
        void process();
};
