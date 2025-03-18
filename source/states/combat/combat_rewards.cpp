#include "combat.h"

GoldReward::GoldReward() : Gui(500, 400, 100, 300) 
{ amount = 0; }
void GoldReward::display() 
{
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}
void GoldReward::process() {}


RelicReward::RelicReward() : Gui(500, 500, 100, 300) 
{ 
    first  = Relic(circlet); 
    second = Relic(circlet); 
}

void RelicReward::display() 
{
    game.render_img("assets/ui/combat/reward_item_panel.png", first.rect.x,  first.rect.y,  rect.w, rect.h, 255, NULL);
    game.render_img("assets/ui/combat/reward_item_panel.png", second.rect.x, second.rect.y, rect.w, rect.h, 255, NULL);
}
void RelicReward::process() {}


ChooseCardReward::ChooseCardReward() : Gui(500, 600, 100, 300) 
{ 
    choices = vector<Card>(3); 
}
void ChooseCardReward::display() 
{
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}
void ChooseCardReward::process() {}


RewardMenu::RewardMenu() : Gui(480, 380, 140, 1000) { tick = 0; }
void RewardMenu::display() 
{
    game.render_img("assets/ui/combat/reward_sheet.png", 300, 200, 400, 600, 255, NULL);
    gReward.display();
    rReward.display();
    ccReward.display();
}
bool RewardMenu::process() 
{
    display();
    tick++;
    if (tick == 360) return true;
    return false;
}

void RewardMenu::generate_items()
{
    gReward.amount = rand() % 100;
    ccReward.choices.clear();
    ccReward.choices.resize(3);
    for (int i{0}; i < 3; i++)
    {
        shuffle_vector(commonCardPool); shuffle_vector(uncommonCardPool); shuffle_vector(rareCardPool);
        vector<cardIdInv>* poolRand;
        int seed = rand() % 10;
        if      (seed >= 0 && seed < 6) poolRand = &commonCardPool;            
        else if (seed >= 6 && seed < 9) poolRand = &uncommonCardPool;
        else                            poolRand = &rareCardPool;
        ccReward.choices[i] = Card(poolRand->front(), i);
        ccReward.choices[i].move_rect(160+200*i, 100);
    }


    vector<relicId> copyCommon  (  commonRelicPool.begin(),   commonRelicPool.end());
    vector<relicId> copyUncommon(uncommonRelicPool.begin(), uncommonRelicPool.end());
    vector<relicId>* copy;
    int seed = rand() % 10;
    if (seed >= 0 && seed < 8) copy = &copyCommon;            
    else copy = &copyUncommon;
    shuffle_vector(*copy);
    if (copy->size() == 0) rReward.first = Relic(circlet);
    else
    {
        rReward.first = Relic(copy->front());
        copy->erase(copy->begin());
    }
    rReward.first.move_rect(580+130, 405+175);
    shuffle_vector(*copy);
    if (copy->size() == 0) rReward.second = Relic(circlet);
    else
    {
        rReward.second = Relic(copy->front());
        copy->erase(copy->begin());
    }
    rReward.second.move_rect(580+130, 405+175);
}

