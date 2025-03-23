#pragma once

#include <map>
#include <functional>
#include "../gui/gui.h"

enum relicId {
    circlet, anchor, blood_vial, shuriken, gremlin_horn, singing_bowl,
    bronze_scales, tea_set
};

struct relicAttributes
{
    const char* sprite;
    std::function<void()> effect;
};

class Relic : public Gui
{
    public:
        Relic();
        Relic(relicId id_);
        void display();
        bool active{true};
        relicId id{circlet};
        relicAttributes attributes;
        static const unordered_map<relicId, relicAttributes> relAttriMap;
};


enum statusId {
    weakness, strength, vulnerable, thorns,  
};

struct status
{
    int level;
    double value;
    const char* sprite;
    Text levelText = Text(0,0,0,0,0,0);
};

static map<statusId, status> globalStatuses = {
    {weakness,   {0, 0.25, "assets/ui/combat/status/weak.png"}},
    {strength,   {0, 1   , "assets/ui/combat/status/strength.png"}},
    {vulnerable, {0, 0.5 , "assets/ui/combat/status/vulnerable.png"}},
    {thorns,     {0, 1   , "assets/ui/combat/status/thorns.png"}}
};
