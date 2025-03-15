#pragma once

enum relicId {
    anchor
};

struct relicAttributes
{
    string sprite;
};

class Relic : public Gui
{
    public:
        Relic(relicId id_);
        void display();
        bool status{true};
        relicId id;
        relicAttributes attributes;
};
