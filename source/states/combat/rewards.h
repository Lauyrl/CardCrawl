#pragma once
// doi ten tu combat rewards
#include <utility>
#include "../../game.h"
#include "../../gui/gui.h"
#include "../../cards/deck.h"
#include "../../gui/top_panel.h"

class GoldReward : public Gui
{
    public:
        GoldReward();
        void display();
        void process();
        int amount{0};
        Text amountText = Text(28, rect.x+98, rect.y+32, 20, 20, 20);
        bool used{false};
};
class RelicReward : public Gui
{
    public:
        RelicReward(int order_);
        void display(bool pairUsed, bool pairHovered, bool cc);
        void process();
        int order;
        Relic relic;
        set<relicId>* pool;
        Text warningText = Text(0,0,0,0,0,0);
        bool used{false};
};
class RelicRewardPair
{
    public:
        RelicRewardPair();
        void display(bool cc);
        void process();
        RelicReward first  = RelicReward(0);
        RelicReward second = RelicReward(1);
        bool used{false};
};
class ChooseCardReward : public Gui
{
    public:
        ChooseCardReward();
        void display();
        void process();
        vector<Card> choices;
        bool active{false};
        bool used{false};
};
class RewardMenu : public Gui
{
    public:
        RewardMenu(bool gold_ = true, bool relic_ = true, bool card_ = true);
        void display();
        bool process();
        void generate_items(int gMin, int gMax, int cUncomThres, int cRareThres, int cMax, int rUncomThres, int rRareThres, int rMax);
        bool gold;
        bool relic;
        bool cards;
        GoldReward gReward;
        ChooseCardReward ccReward;
        RelicRewardPair rRewardPair;
};
