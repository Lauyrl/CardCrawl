#pragma once

#include <iostream>
#include "../gui/gui.h"
#include "../game.h"

using namespace std;

class EndTurnButton : public Gui 
{
    public:
        EndTurnButton();
        void et_button_display();
        Text labelText;
};
EndTurnButton et_button_init();

class EnergyUi : public Gui
{
    public:
        EnergyUi();
        void energy_display();
        Text energyText;

};
EnergyUi eu_init();
