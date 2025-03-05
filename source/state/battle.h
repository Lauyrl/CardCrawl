#pragma once

#include "battle_ui.h"
#include "../game.h"
#include "../cards/deck.h"

const int MAX_ENEMIES = 3;

SDL_Rect background{0, 280, 1920, 1225};
EndTurnButton etButton;
DrawPileButton drpButton;
DiscardPileButton dcpButton;

int turn{0};
static Deck deckObj(DECK_MAX_SIZE);
static std::vector<Enemy> stageEnemies;
int activeEnemyIdx{0};
bool playerTurn{false};
