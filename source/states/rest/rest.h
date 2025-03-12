#pragma once

#include "../../character/character.h"

enum restOption{
    sleep
};
class Option : public Gui
{
    public:
        Option(restOption op_);
        void display();
        void effect();
        restOption op;
        static bool selected;
        static const map<restOption, const char*> opMap; 
};

Option sleepOp(sleep);
static bool restInit{true};
