#include "battle_ui.h"

extern Game game;

EndTurnButton::EndTurnButton() : Gui(900, 100, 100, 40) {}

void EndTurnButton::et_button_display()
{
    SDL_SetRenderDrawColor(game.renderer, 0, 60, 120, 100);
    SDL_RenderFillRect(game.renderer, &rect);
    etText.render_text("End Turn");
}
