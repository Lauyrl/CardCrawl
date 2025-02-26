#pragma once

#include <vector>
#include "../cards/deck.h"
#include "../game.h"

const int MAX_ENEMIES = 3;

SDL_Rect background{0, 380, 1920, 1225};
static Deck deckObj(0);
static Enemy test;
static std::vector<Enemy> stage_enemies(MAX_ENEMIES);
size_t numOfEnemies{MAX_ENEMIES};
