#pragma once

#include <vector>
#include "../cards/deck.h"
#include "../enemies/enemy.h"
#include "../game.h"

const int MAX_ENEMIES = 3;

static Deck deckObj(0);
static Enemy test;
static std::vector<Enemy> stage_enemies(MAX_ENEMIES);


//each battle instance should hold a container of enemies
