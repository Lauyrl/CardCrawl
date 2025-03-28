#pragma once

#include "../game.h"
#include "../gui/gui.h"
#include "../character/character.h"
enum intentId {
    attack1, attack2, attack3, attack4, attack5, attack6 , attack7, 
    debuff1attack1, debuff1attack2, debuff1attack3, debuff1attack4, debuff1attack5, debuff1attack6, debuff1attack7, 
    debuff1, debuff2, debuff1defend,
    defense, defendbuff, 
    defendattack1, defendattack2, defendattack3, defendattack4, defendattack5, defendattack6, defendattack7,
    buff, buffattack3, sleeping, unknown
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

