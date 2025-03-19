#pragma once

#include <functional>
#include "../../game.h"
#include "../../gui/top_panel.h" //includes character
#include "id_to_event.h"
#include "../../cards/deck.h"
class Event
{
    public:
        Event();
        void process();
        void generate();
        Text title = Text(50, 260, 170, 255, 255, 255);
        Text desc  = Text(24, 620, 280, 255, 255, 255);
        eventId id;
        eventAttributes attributes;
        static bool inMenu;
        bool complete{false};
        static const map<eventId, eventAttributes> evAttriMap;
};

class Choice : public Gui
{
    public:
        Choice(choiceId id_, int pos_);
        void display();
        bool process();
        int pos;
        bool chosen{false};
        int currentUses;
        Text label = Text(24, rect.x+50, rect.y+8, 255, 255, 255);
        choiceId id;
        choiceAttributes attributes;
        static const map<choiceId, choiceAttributes> choiceAttriMap;
};
