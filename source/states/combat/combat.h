#pragma once

#include "combat_ui.h"
#include "combat_rewards.h"
#include "../map/map.h"
#include "../../pools/pools.h"

const int MAX_ENEMIES = 3; /////////////////////////////////////////////////////////

extern SDL_Rect background;
extern EndTurnButton etButton;
extern DrawPileButton drpButton;
extern DiscardPileButton dcpButton;
extern vector<Enemy> stageEnemies;
extern vector<enemyId> possibleEnemies;
extern int turn;
extern int activeEnemyIdx;
extern bool inMenu;
extern bool charaRenew;
extern RewardMenu rMenu;

void init_components(vector<Enemy> &stageEnemies);
void piles_process(DiscardPileButton &dcp, DrawPileButton &drp);
void enemy_process(vector<Enemy> &stageEnemies);
bool enemy_turn(vector<Enemy> &stageEnemies);
void combat_win();
