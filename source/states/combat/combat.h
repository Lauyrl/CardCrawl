#pragma once

#include "combat_ui.h"
#include "rewards.h"
#include "../map/map_elements.h"
#include "../../pools/pools.h"

const int MAX_ENEMIES = 3; /////////////////////////////////////////////////////////

static SDL_Rect black{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
static SDL_Rect background{0, 280, 1920, 1225};
extern EndTurnButton et;
extern DrawPileButton drp;
extern DiscardPileButton dcp;
extern vector<Enemy> stageEnemies;
extern vector<enemyId> possibleEnemies;
extern RewardMenu rMenu;
extern int turn;
extern int activeEnemyIdx;
extern bool inMenu;
extern bool firstTurn;
extern bool charaRenewTurn;

void renew_combat();
void init_combat();
void piles_process();
void enemy_generate_intents();
void enemy_process();
bool enemy_turn();
void combat_win();
bool death();
