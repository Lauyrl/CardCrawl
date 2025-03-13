#pragma once

#include "combat_ui.h"
#include "../map/map.h"

const int MAX_ENEMIES = 1; /////////////////////////////////////////////////////////

SDL_Rect background{0, 280, 1920, 1225};
static EndTurnButton etButton;
static DrawPileButton drpButton;
static DiscardPileButton dcpButton;
static Deck deckObj(DECK_MAX_SIZE); 
//mind repeated definitions for these
std::vector<enemyId> possibleEnemies = {acid_slime, cultist, cultist, acid_slime, cultist};
static std::vector<Enemy> stageEnemies;
int turn{0};
int activeEnemyIdx{0};
bool charaRenew{false};
bool inMenu{false};

void init_components(Deck &deckObj, vector<Enemy> &stageEnemies)
{
    turn = 0;
    deckObj.discardPile.clear();
    deckObj.drawPile.clear();
    deckObj.set_up_dp();
    deckObj.build_hand();
    ironclad.reset_energy();
    shuffle_vector(possibleEnemies);
    for (int i{0}; i < MAX_ENEMIES; i++)
    {
        stageEnemies.push_back(Enemy(possibleEnemies[i], i));
    }
}

void hand_process(Deck &deckObj)
{
    deckObj.toDiscard = NULL_CARD;
    for (size_t current{0}; current < deckObj.hand.size(); current++)
    {
        deckObj.hand[current].highlight();
        deckObj.hand[current].display();
        if (!inMenu) deckObj.interact_cards(current, stageEnemies); 
    }
    if (deckObj.toDiscard != NULL_CARD) deckObj.discard_card();
}

void piles_process(DiscardPileButton &dcp, DrawPileButton &drp, Deck &deckObj)
{
    if (!drp.displaying) dcp.button_process(deckObj);
    if (!dcp.displaying) drp.button_process(deckObj);
    inMenu = (drp.displaying || dcp.displaying);
}

void enemy_process(vector<Enemy> &stageEnemies)
{
    for (int i{stageEnemies.size()-1}; i >= 0 ; i--)
    {
        if (stageEnemies[i].attributes.hp <= 0) stageEnemies.erase(stageEnemies.begin()+i);
        else stageEnemies[i].display();
    }
}

bool enemy_turn(vector<Enemy> &stageEnemies)
{
    if (!stageEnemies[activeEnemyIdx].enemy_action()) return false; // return true after animation finishes
    else 
    {
        activeEnemyIdx++;
        if (activeEnemyIdx < stageEnemies.size()) return false;
    }
    activeEnemyIdx = 0;
    return true;
}

void combat_win()
{
    game.state_switch(game.gameStates::map);
    stageEnemies.clear();
}
