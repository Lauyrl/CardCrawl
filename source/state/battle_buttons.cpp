#include "battle_buttons.h"

extern Game game;

EndTurnButton::EndTurnButton() : Gui(900, 100, 100, 50) {}

void EndTurnButton::et_button_display()
{
    SDL_Rect et_button_rect{rect.x, rect.y, rect.w, rect.h};
    SDL_SetRenderDrawColor(game.renderer,0,10,120,100);
    SDL_RenderFillRect(game.renderer, &et_button_rect);
}
