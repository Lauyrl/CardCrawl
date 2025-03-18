#include "combat.h"
//đổi tên từ battle.cpp

void Game::display_combat()
{
    // int frameStart = SDL_GetTicks();
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &background);
    if (combatInit)
    {
        init_components(stageEnemies);
        combatInit = false;
    }
    ironclad.display();
    enemy_process(stageEnemies);
    if (stageEnemies.size() == 0) 
    {
        combat_win();
        return;
    }

    if (turn%2 == 0)
    {
        if (charaRenew)
        {
            deck.renew_hand();
            ironclad.block = 0;
            charaRenew = false;
        }
        if (!inMenu && etButton.detect_click()) turn++;
        ironclad.display_energy();
        etButton.display();
        deck.hand_process(inMenu, stageEnemies);
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        if (enemy_turn(stageEnemies)) //wait for enemy_turn() to finish
        {
            ironclad.reset_energy();
            charaRenew = true;
            turn++;
        }
    }
    piles_process(dcpButton, drpButton);
    panel.display();
}

SDL_Rect background = {0, 280, 1920, 1225};
EndTurnButton etButton;
DrawPileButton drpButton;
DiscardPileButton dcpButton;
vector<Enemy> stageEnemies;
vector<enemyId> possibleEnemies = {acid_slime, acid_slime, cultist, cultist, cultist};
RewardMenu rMenu;
int turn = 0;
int activeEnemyIdx = 0;
bool inMenu = false;
bool charaRenew = false;
void init_components(vector<Enemy> &stageEnemies)
{
    turn = 0;
    deck.set_up_piles();
    deck.build_hand();
    ironclad.reset_energy();
    ironclad.combat_start_relic_renew();
    ironclad.combat_start_relic();
    stageEnemies.clear();
    shuffle_vector(possibleEnemies);
    for (int i{0}; i < MAX_ENEMIES; i++) stageEnemies.push_back(Enemy(possibleEnemies[i], i));
    //rMenu.generate_items();
    cout << "Initiation success" << endl;
}

void piles_process(DiscardPileButton &dcp, DrawPileButton &drp)
{
    if (!panel.inMenu)
    {
        if (!drp.displaying) dcp.button_process();
        if (!dcp.displaying) drp.button_process();
    }
    else { drp.displaying = false; dcp.displaying = false; }
    inMenu = (drp.displaying || dcp.displaying || panel.inMenu);
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
    if (rMenu.process())
    {
        stageEnemies.clear();
    //game.combatInit?;
        game.state_switch(game.gameStates::map);
    }
}
