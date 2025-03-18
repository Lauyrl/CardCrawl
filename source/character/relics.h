#pragma once

#include <map>
#include <functional>
#include "../gui/gui.h"

enum relicId {
    circlet, anchor, blood_vial
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
