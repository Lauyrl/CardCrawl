#pragma once

#include <vector>
#include "battle_ui.h"
#include "../cards/deck.h"
#include "../game.h"

const int MAX_ENEMIES = 3;

SDL_Rect background{0, 280, 1920, 1225};
EndTurnButton etButton;

static Deck deckObj(DECK_MAX_SIZE);
static std::vector<Enemy> stageEnemies;
int activeEnemyIdx{0};
int turn{0};
