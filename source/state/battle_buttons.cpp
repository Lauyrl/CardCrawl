#include "battle_buttons.h"

extern Game game;

EndTurnButton::EndTurnButton() : Gui(900, 100, 100, 40) {} //Initing label_text here gives bug

EndTurnButton et_button_init()
{
    EndTurnButton etButton;
    text_init(etButton.labelText, "End Turn", 22, etButton.rect.x+9, etButton.rect.y+3, 1, 1, 250, 250, 250);
    return etButton;
}

void EndTurnButton::et_button_display()
{
    SDL_SetRenderDrawColor(game.renderer, 0, 60, 120, 100);
    SDL_RenderFillRect(game.renderer, &rect);
    labelText.render_text();
}

EnergyUi::EnergyUi() : Gui(120, 400, 60, 60) {}

EnergyUi eu_init()
{
    EnergyUi eu;
    text_init(eu.energyText, "3/3", 30, eu.rect.x+7, eu.rect.y+10, 1, 1, 50, 100, 100);
    return eu;
}

void EnergyUi::energy_display()
{
    game.render_img("assets/ui/red_energy.png", rect.x, rect.y, rect.w, rect.h, NULL);
    energyText.render_text();
}
