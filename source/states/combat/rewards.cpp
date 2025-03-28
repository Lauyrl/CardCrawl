#include "combat.h"

GoldReward::GoldReward() : Gui(465, 270, 510, 100) {};
void GoldReward::display() 
{
    Uint8 alpha = (used)? 100:240;
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, alpha, NULL);
    game.render_img("assets/ui/gold.png", rect.x+23, rect.y+16, 70, 70, alpha, NULL);
    amountText.render_text(to_string(amount)+" gold");

}
void GoldReward::process() 
{
    if (!panel.inMenu && !used && detect_click())
    {
        ironclad.gold += amount;
        used = true;
    }
}

RelicReward::RelicReward(int order_) : Gui(465, 370+100*order_, 510, 100) 
{ 
    order = order_; 
    warningText = Text(20, rect.x+290, rect.y+37, 240, 40, 40);
}
void RelicReward::display(bool pairUsed, bool pairHovered, bool cc) 
{
    Uint8 alpha;
    if  (pairUsed) alpha = 20;
    else if (used) alpha = 100;
    else           alpha = 240;
    game.render_img("assets/ui/combat/reward_item_panel.png", rect.x, rect.y, rect.w, rect.h, alpha, NULL);
    relic.move_rect(rect.x+28, rect.y);
    relic.display(DISPLAY_DESC, false);
    Uint8 r = (pairHovered&&!used&&!pairUsed)?200:20;
    Uint8 g = (pairHovered&&!used&&!pairUsed)?21:20;
    relic.nameText = Text(28, rect.x+100, rect.y+32, r, g, 20);
    relic.nameText.render_text(relic.attributes.name);
    if (!cc && detect_cursor_hover()) relic.display_info(DISPLAY_DESC);
    warningText.render_text("(You can only pick one.)");
}
void RelicReward::process() 
{
    if (!panel.inMenu && detect_click())
    {
        ironclad.add_relic(relic.id);
        if (relic.id != circlet) pool->erase(relic.id);
        used = true;
    }
}

RelicRewardPair::RelicRewardPair() {}
void RelicRewardPair::display(bool cc) 
{
    first.display(second.used, second.detect_cursor_hover(), cc);
    second.display(first.used,  first.detect_cursor_hover(), cc);
    game.render_img("assets/ui/combat/relic_link.png", 640, 395, 150, 150, 220, NULL);

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
                deck.add_card(choices[i].id);
                choices.erase(choices.begin()+i);
                active = false;
                used = true;
                break;
            }
        }
    }
}

RewardMenu::RewardMenu(bool gold_, bool relic_, bool cards_) : Gui(280, 100, 880, 640) 
{
    gold = gold_;
    relic = relic_;
    cards = cards_;
}
void RewardMenu::display() 
{
    game.render_img("assets/ui/combat/reward_sheet.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
    if (gold) gReward.display();
    if (relic) rRewardPair.display(ccReward.active);
    if (cards) ccReward.display();
}
bool RewardMenu::process() 
{
    display();
    if (cards) 
    {
        ccReward.process();
        if (ccReward.active) return false;
    }
    else    ccReward.used = true;
    if (gold) gReward.process();
    else     gReward.used = true;
    if (relic) rRewardPair.process();
    else rRewardPair.used = true;
    return (gReward.used && rRewardPair.used && ccReward.used);
}
void RewardMenu::generate_items(int gMin, int gMax, int cUncomThres, int cRareThres, int cMax, int rUncomThres, int rRareThres, int rMax)
{
    gReward.used = false;
    if (gold) gReward.amount = rand_int(gMin, gMax);
    ccReward.used = false; ccReward.active = false;
    if (cards)
    {
        ccReward.choices.clear();
        ccReward.choices.resize(3);
        for (int i{0}; i < 3; i++)
        {
            shuffle_vector(commonCardPool); shuffle_vector(uncommonCardPool); shuffle_vector(rareCardPool);
            vector<cardId>* poolRand;
            int seed = rand_int(0, cMax);
            if (seed >= 0 && seed < cUncomThres) poolRand = &commonCardPool;            
            else if (seed >= cUncomThres && seed < rRareThres) poolRand = &uncommonCardPool;
            else poolRand = &rareCardPool;
            ccReward.choices[i] = Card(poolRand->front(), i);
            ccReward.choices[i].move_rect(160+200*i, 100);
        }
    }
    rRewardPair.used = false; rRewardPair.first.used = false; rRewardPair.second.used = false;
    if (relic)
    {
        vector<relicId> copyRare (rareRelicPool.begin(), rareRelicPool.end());
        vector<relicId> copyCommon (commonRelicPool.begin(), commonRelicPool.end());
        vector<relicId> copyUncommon (uncommonRelicPool.begin(), uncommonRelicPool.end());
        vector<relicId>* copy;
        int seed = rand_int(0, rMax);
        if (seed >= 0 && seed < rUncomThres) 
        {
            copy = &copyCommon;
            rRewardPair.first.pool = &commonRelicPool;
            rRewardPair.second.pool = &commonRelicPool;
        }
        else if (seed >= rUncomThres)
        {
            copy = &copyUncommon;
            rRewardPair.first.pool = &uncommonRelicPool;
            rRewardPair.second.pool = &uncommonRelicPool;
        }
        else
        {
            copy = &copyRare;
            rRewardPair.first.pool = &rareRelicPool;
            rRewardPair.second.pool = &rareRelicPool;
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
}
