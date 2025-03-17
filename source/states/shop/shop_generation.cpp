#include "shop.h"

void Shop::generate_items()
{
    shopCards.clear()  ; shopRelics.clear();
    shopCards.resize(8); shopRelics.resize(6);
    for (int i{0}; i < 8; i++)
    {
        shuffle_vector(commonCardPool); shuffle_vector(uncommonCardPool); shuffle_vector(rareCardPool);
        int seed = rand() % 10;
        int costRand;
        vector<cardIdInv>* poolRand;
        if (seed >= 0 && seed < 6)
        {
            costRand = rand() % 8 + 20;
            poolRand = &commonCardPool;            
        }
        else if (seed >= 6 && seed < 9) 
        {
            costRand = rand() % 12 + 38;
            poolRand = &uncommonCardPool;
        }
        else                            
        {
            costRand = rand() % 18 + 56;
            poolRand = &rareCardPool;
        }
        shopCards[i] = CardItem(costRand, Card((*poolRand)[0], i));
        shopCards[i].pool = poolRand;
        shopCards[i].card.move_rect(160+200*(i%6), 100+320*(i/6));
        shopCards[i].costText = Text(20, shopCards[i].card.rect.x+81, shopCards[i].card.rect.y+240,255,255,255);
    }


    vector<relicId> copyCommon(commonRelicPool.begin(), commonRelicPool.end());
    vector<relicId> copyUncommon(uncommonRelicPool.begin(), uncommonRelicPool.end());
    vector<relicId> copyRare(rareRelicPool.begin(), rareRelicPool.end());
    for (int i{0}; i < 6; i++)
    {
        int seed = rand() % 10;
        int costRand;
        set<relicId>* poolRand;
        vector<relicId>* copy;
        if (seed >= 0 && seed < 6)
        {
            costRand = rand() % 8 + 20;
            poolRand = &commonRelicPool;
            copy = &copyCommon;            
        }
        else if (seed >= 6 && seed < 8) 
        {
            costRand = rand() % 12 + 38;
            poolRand = &uncommonRelicPool;
            copy = &copyUncommon;
        }
        else                            
        {
            costRand = rand() % 18 + 56;
            poolRand = &rareRelicPool;
            copy = &copyRare;
        }
        shuffle_vector(*copy);
        if (copy->size() == 0) shopRelics[i] = RelicItem(100, Relic(circlet));
        else
        {
            shopRelics[i] = RelicItem(costRand, Relic((*copy)[0]));
            copy->erase(copy->begin());
        }
        shopRelics[i].pool = poolRand;
        shopRelics[i].relic.move_rect(580+130*(i%3), 405+175*(i/3));
        shopRelics[i].costText = Text(20, shopRelics[i].relic.rect.x+37, shopRelics[i].relic.rect.y+80,255,255,255);
    }
}
