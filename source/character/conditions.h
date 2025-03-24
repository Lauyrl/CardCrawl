#pragma once

#include <map>
#include <functional>
#include "../gui/gui.h"

const int DISPLAY_FULL = 0;
const int DISPLAY_DESC = 1;
enum relicId {
    circlet, anchor, blood_vial, shuriken, gremlin_horn, singing_bowl,
    bronze_scales, tea_set
};

struct relicAttributes
{
    string name;
    std::function<void()> effect;
    string desc;
};

class Relic : public Gui
{
    public:
        Relic();
        Relic(relicId id_);
        void display(int where = DISPLAY_FULL, bool info = true);
        void display_info(int where = DISPLAY_FULL);
        bool active{true};
        relicId id{circlet};
        relicAttributes attributes;
        Text nameText = Text(0, 0, 0, 0, 0, 0);
        Text descText = Text(0, 0, 0, 0, 0, 0);
        static const unordered_map<relicId, relicAttributes> relAttriMap;
};


enum statusId {
    weakness, strength, vulnerable, thorns,  
};

struct Status : public Gui
{
    Status(int level_, double value_, const char* sprite_, string desc_) : Gui(0,0,0,0), level(level_), value(value_), sprite(sprite_), desc(desc_) {}
    Status() : Gui(0,0,0,0) {}
    void display();
    void display_desc();
    int level;
    double value;
    const char* sprite;
    string desc;
    Text levelText = Text(0,0,0,0,0,0);
    Text descText = Text(0,0,0,0,0,0);
};

static map<statusId, Status> globalStatuses = {
    {weakness,   Status(0, 0.25, "assets/ui/combat/status/weak.png"      , "Deal 25% less damage (X turns)\nCurrent X: ")},
    {strength,   Status(0, 1   , "assets/ui/combat/status/strength.png"  , "Deal X additional damage\nCurrent X: ")},
    {vulnerable, Status(0, 0.5 , "assets/ui/combat/status/vulnerable.png", "Receive 25% more damage (X turns)\nCurrent X: ")},
    {thorns,     Status(0, 1   , "assets/ui/combat/status/thorns.png"    , "Attackers receive X damage\nCurrent X: ")}
};
