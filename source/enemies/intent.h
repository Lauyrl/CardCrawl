#pragma once

#include "../game.h"
#include "../gui/gui.h"
#include "../character/character.h"
enum intentId {
    attack1, attack2, attack3, attack4, attack5 ,attack6 , attack7, 
    debuff1, debuff2, buff1, defend1, 
    attack1debuff1
};
struct IntentAttributes 
{
    const char* sprite;
    string desc;
};
class Intent : public Gui
{
    public:
        Intent();
        Intent(intentId id);
        void display(int x, int y);
        void display_desc();
        intentId id;
        IntentAttributes attributes;
        Text descText = Text(0,0,0,0,0,0);
        static const unordered_map<intentId, IntentAttributes> intentAttriMap;
};

