#include "combat.h"

GoldReward::GoldReward() : Gui(465, 270, 510, 100) {};
void GoldReward::display() 
{
    Uint8 alpha = (used)? 100:240;
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, alpha, NULL);
    game.render_img("assets/ui/gold.png", rect.x+23, rect.y+16, 70, 70, alpha, NULL);
    amountText.render_text(to_string(amount));

}
void GoldReward::process() 
{
    if (!panel.inMenu && !used && detect_click())
    {
        ironclad.gold += amount;
        used = true;
    }
}

RelicReward::RelicReward(int order_) : Gui(465, 370+100*order_, 510, 100) { order = order_; }
void RelicReward::display(bool pairUsed) 
{
    Uint8 alpha = (used)? 100:240;
    if (pairUsed) alpha = 20;
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, alpha, NULL);
    relic.move_rect(rect.x+12, rect.y);
    relic.display();
}
void RelicReward::process() 
{
    if (!panel.inMenu && detect_click())
    {
        ironclad.relicInv.push_back(Relic(relic.id));
        if (relic.id != circlet) pool->erase(relic.id);
        used = true;
    }
}

RelicRewardPair::RelicRewardPair() {}
void RelicRewardPair::display() 
{
    first.display(second.used);
    second.display(first.used);
    game.render_img("assets/ui/combat/relic_link.png", 640, 393, 150, 150, 200, NULL);

}
void RelicRewardPair::process() 
{
    used = (first.used || second.used); if (!used) first.process();
    used = (first.used || second.used); if (!used) second.process();
}

ChooseCardReward::ChooseCardReward() : Gui(465, 570, 510, 100) {}
void ChooseCardReward::display() 
{
    Uint8 alpha = (used || active)? 100:240;
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, alpha, NULL);
    game.render_img("assets/ui/combat/normal_card_reward.png", rect.x+22, rect.y+15, 70, 70, alpha, NULL);
    if (active)
        for (int i{0}; i < 3; i++) choices[i].display_copy(400+i*250, 320, true, true);
}
void ChooseCardReward::process() 
{
    if (!panel.inMenu && !used && detect_click()) active = true;
    if (active)
    {
        for (int i{2}; i >= 0; i--)
        {
            if (!panel.inMenu && choices[i].detect_click())
            {
                ironclad.cardIdInv.push_back(choices[i].id);
                choices.erase(choices.begin()+i);
                active = false;
                used = true;
                break;
            }
        }
    }
}

RewardMenu::RewardMenu() : Gui(280, 100, 880, 640) {}
void RewardMenu::display() 
{
    game.render_img("assets/ui/combat/reward_sheet.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
    gReward.display();
    rRewardPair.display();
    ccReward.display();
}
bool RewardMenu::process() 
{
    display();
    ccReward.process();
    if (ccReward.active) return false;
    gReward.process();
    rRewardPair.process();
    return (gReward.used && rRewardPair.used && ccReward.used);
}
void RewardMenu::generate_items()
{
    gReward.used = false;
    gReward.amount = rand_int(0, 100);

    ccReward.used = false; ccReward.active = false;
    ccReward.choices.clear();
    ccReward.choices.resize(3);
    for (int i{0}; i < 3; i++)
    {
        shuffle_vector(commonCardPool); shuffle_vector(uncommonCardPool); shuffle_vector(rareCardPool);
        vector<cardIdInv>* poolRand;
        int seed = rand_int(0, 10);
        if      (seed >= 0 && seed < 6) poolRand = &commonCardPool;            
        else if (seed >= 6 && seed < 9) poolRand = &uncommonCardPool;
        else                            poolRand = &rareCardPool;
        ccReward.choices[i] = Card(poolRand->front(), i);
        ccReward.choices[i].move_rect(160+200*i, 100);
    }

    rRewardPair.used = false; rRewardPair.first.used = false; rRewardPair.second.used = false;
    vector<relicId> copyCommon (commonRelicPool.begin(), commonRelicPool.end());
    vector<relicId> copyUncommon (uncommonRelicPool.begin(), uncommonRelicPool.end());
    vector<relicId>* copy;
    int seed = rand_int(0, 10);
    if (seed >= 0 && seed < 8) 
    {
        copy = &copyCommon;
        rRewardPair.first.pool = &commonRelicPool;
        rRewardPair.second.pool = &commonRelicPool;
    }
    else 
    {
        copy = &copyUncommon;
        rRewardPair.first.pool = &uncommonRelicPool;
        rRewardPair.second.pool = &uncommonRelicPool;
    }
    for (int i{0}; i < 2; i++)
    {
        RelicReward* current;
        if (i == 0) current = &rRewardPair.first;
        else        current = &rRewardPair.second;
        shuffle_vector(*copy);
        if (copy->size() == 0) current->relic = Relic(circlet);
        else
        {
            current->relic = Relic(copy->front());
            copy->erase(copy->begin());
        }
        current->relic.move_rect(580+130, 405+175);
    }
}
