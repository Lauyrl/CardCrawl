#pragma once

#include "combat_ui.h"
#include "../../game.h"
#include "../../cards/deck.h"
#include "../map/map.h"

const int MAX_ENEMIES = 3;

extern Game game; 
extern Character ironclad;

SDL_Rect background{0, 280, 1920, 1225};
EndTurnButton etButton;
DrawPileButton drpButton;
DiscardPileButton dcpButton;
//mind repeated definitions for these
static Deck deckObj(DECK_MAX_SIZE); //?
bool rebuildHand{false};
std::vector<enemyId> possibleEnemies = {acid_slime, cultist, cultist, acid_slime, cultist};
static std::vector<Enemy> stageEnemies;
int activeEnemyIdx{0};
int turn{0};


void init_components(Deck &deckObj, vector<Enemy> &stageEnemies)
{
    turn = 0;
    deckObj.set_up_draw_pile(ironclad);
    deckObj.discardPile.clear();
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
        deckObj.interact_cards(current, ironclad, stageEnemies); 
    }
    if (deckObj.toDiscard != NULL_CARD) 
    {
        deckObj.discardPile.push_back(deckObj.hand[deckObj.toDiscard]);
        deckObj.discard_card();
    }
}

void piles_process(DiscardPileButton &dcp, DrawPileButton &drp, Deck &deckObj)
{
    drp.display();
    dcp.display();
    if (drp.detect_click()) 
    {
        for (size_t i{0}; i < deckObj.drawPile.size(); i++)
        {
            cout << deckObj.drawPile[i].id << ' ';
        }
        cout << endl;
    }
    if (dcp.detect_click()) 
    {
        for (size_t i{0}; i < deckObj.discardPile.size(); i++)
        {
            cout << deckObj.discardPile[i].id << ' ';
        }
        cout << endl;
    }
}

void enemy_process(vector<Enemy> &stageEnemies)
{
    for (int i{stageEnemies.size()-1}; i >= 0 ; i--)
    {
        if (stageEnemies[i].attributes.hp <= 0) stageEnemies.erase(stageEnemies.begin()+i);
        else stageEnemies[i].display();
    }
}

bool enemy_turn(Character &chara, vector<Enemy> &stageEnemies)
{
    if (!stageEnemies[activeEnemyIdx].enemy_action(ironclad)) return false; // return true after animation finishes
    else 
    {
        game.tick = 0;
        activeEnemyIdx++;
        if (activeEnemyIdx < stageEnemies.size()) return false;
    }
    activeEnemyIdx = 0;
    return true;
}

void combat_win()
{
    game.gameState = game.gameStates::map;
    stageEnemies.clear();
}
