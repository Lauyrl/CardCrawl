#include "combat.h"

void Game::display_combat()
{
    // int frameStart = SDL_GetTicks();
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &background);
    if (combatInit)
    {
        init_combat();
        combatInit = false;
    }
    ironclad.display();
    enemy_process();
    if (death()) return;
    if (stageEnemies.size() == 0) 
    {
        combat_win();
        return;
    }
    if (turn%2 == 0)
    {
        if (charaRenewTurn)
        {
            ironclad.renew_turn(); //renew deck first or ironclad first
            deck.renew_hand();
            ironclad.block=0;
            enemy_generate_intents();
            charaRenewTurn = false;
        }
        if (turn == 0 && firstTurn) { ironclad.combat_start_relic(); firstTurn = false; }
        if (!inMenu && et.detect_click()) 
        { 
            ironclad.decrement_statuses(); 
            for (auto& enemy:stageEnemies) enemy.block = 0;
            turn++;
        }
        ironclad.display_energy();
        deck.hand_process(inMenu, stageEnemies);
        ironclad.during_turn_relic();
        et.display();
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        if (enemy_turn()) //wait for enemy_turn() to finish
        {
            for (auto& enemy:stageEnemies) enemy.decrement_statuses();
            charaRenewTurn = true;
            turn++;
        }
    }
    piles_process();
    panel.display();
}


EndTurnButton et;
DrawPileButton drp;
DiscardPileButton dcp;
vector<vector<vector<enemyId>>> formations = {
    //{{awakened}},
    {{acid_slime, acid_slime}, {slaver_blue, slaver_blue}, {snake_plant}}, //{cultist, cultist}
    {{nemesis}, {champ}},
    {{awakened}}
};
vector<Enemy> stageEnemies;
RewardMenu rMenu;
int turn = 0;
int activeEnemyIdx = 0;
bool inMenu = false;
bool firstTurn = true;
bool charaRenewTurn = true;

void renew_combat() { activeEnemyIdx = 0 ; turn = 0; firstTurn = true; charaRenewTurn = true; inMenu = false; }

void enemy_generate()
{
    stageEnemies.clear();
    shuffle_vector(formations[game.combatType]);
    vector<enemyId> chosen = formations[game.combatType].front();
    int x{ENEMY_POS_X};
    for (int i{0}; i < chosen.size(); i++) 
    {   
        stageEnemies.push_back(Enemy(chosen[i], i, x));
        x += 235+50*stageEnemies.back().attributes.size;
    }
}

void init_combat()
{
    renew_combat();
    deck.set_up_piles();
    ironclad.renew();
    enemy_generate();
    rMenu.generate_items(20+100*game.combatType, 100+100*game.combatType, 6-6*game.combatType, 10-3*game.combatType, 9, 7-7*game.combatType, 10-3*game.combatType, 9);
    cout << "Initiation success" << endl;
}

void piles_process()
{
    if (!panel.inMenu)
    {
        if (!drp.displaying) dcp.button_process();
        if (!dcp.displaying) drp.button_process();
    }
    else { drp.displaying = false; dcp.displaying = false; }
    inMenu = (drp.displaying || dcp.displaying || panel.inMenu);
}

void enemy_process()
{
    for (int i{stageEnemies.size()-1}; i >= 0 ; i--)
    {
        if (stageEnemies[i].attributes.hp <= 0) 
        {
            stageEnemies.erase(stageEnemies.begin()+i);
            if (ironclad.check_relic(gremlin_horn)) ironclad.relicInv.at(gremlin_horn).attributes.effect(); 
        }
        else stageEnemies[i].display();
    }
}

void enemy_generate_intents() { for (auto& enemy:stageEnemies) enemy.generate_intent(turn); }

bool enemy_turn()
{
    if (!stageEnemies[activeEnemyIdx].action()) return false; // return true after animation finishes
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
        game.combatInit = true;
        game.state_switch(game.gameStates::map);
    }
    panel.display();
}

bool death()
{   
    static int t{0};
    if (ironclad.health <= 0)
    {
        t++;
        if (t < 60)
        {
            SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255/60*t);
            SDL_RenderFillRect(game.renderer, &black);
        }
        else if (t == 80)
        {
            t = 0;
            game.combatInit = true;
            game.mapGenerated = false;
            game.state_switch(Game::gameStates::start_menu);
        }
        else
        {
            SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(game.renderer, &black);
        }
        return true;
    }
    else return false;
}
