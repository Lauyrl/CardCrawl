#pragma once

#include "../../gui/top_panel.h"

enum restOption{
    sleep
};
class Option : public Gui
{
    public:
        Option(restOption op_);
        void display();
        void process();
        restOption op;
        static bool selected;
        static const map<restOption, const char*> opMap; 
};

Option sleepOp(sleep);

