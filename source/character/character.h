#pragma once

#include <vector>
#include "../gui/gui.h"

enum cardId {
    strike,
    defend
};

class Character : public Gui
{
    public:
        Character(int health);
        Character init(int health);
        void character_display();
        
        static int health;
        static int energy;
        static std::vector<cardId> cardInventoryId;
};

