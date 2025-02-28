#pragma once

#include <vector>
#include "battle_buttons.h"
#include "../cards/deck.h"
#include "../game.h"

const int MAX_ENEMIES = 3;

SDL_Rect background{0, 380, 1920, 1225};
static EndTurnButton etButton;
static EnergyUi eu;

static Deck deckObj(0);
static std::vector<Enemy> stage_enemies(MAX_ENEMIES);
static int turn{0};
