#pragma once

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
        int amount;
};
class RelicReward : public Gui
{
    public:
        RelicReward();
        void display();
        void process();
        Relic first;
        Relic second;
};
class ChooseCardReward : public Gui
{
    public:
        ChooseCardReward();
        void display();
        void process();
        vector<Card> choices;
};
class RewardMenu : public Gui
{
    public:
        RewardMenu();
        void display();
        bool process();
        void generate_items();
        GoldReward gReward = GoldReward();
        RelicReward rReward = RelicReward();
        ChooseCardReward ccReward = ChooseCardReward();
};
