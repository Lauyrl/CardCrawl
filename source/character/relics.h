#pragma once

#include <map>
#include <functional>
#include "../gui/gui.h"
enum relicId {
    anchor, blood_vial
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
        relicId id;
        relicAttributes attributes;
        static const map<relicId, relicAttributes> relAttriMap;
};
