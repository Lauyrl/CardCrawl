#include "shop.h"

void Shop::generate_items()
{
    shopCards.clear()  ; shopRelics.clear();
    shopCards.resize(8); shopRelics.resize(6);
    for (int i{0}; i < 8; i++)
    {
        int seed = rand_int(0, 9);
        int costRand;
        vector<cardId>* poolRand;
        if (seed >= 0 && seed < 6)
        {
            costRand = rand_int(20, 28);
            poolRand = &commonCardPool;            
        }
        else if (seed >= 6 && seed < 9) 
        {
            costRand = rand_int(38, 50);
            poolRand = &uncommonCardPool;
        }
        else                            
        {
            costRand = rand_int(56, 74);
            poolRand = &rareCardPool;
        }
        shuffle_vector(*poolRand);
        shopCards[i] = CardItem(costRand, Card(poolRand->front(), i));
        //cout << "generated card id" << poolRand->front() << endl;
        shopCards[i].pool = poolRand;
        shopCards[i].card.move_rect(160+200*(i%6), 100+320*(i/6));
        shopCards[i].costText = Text(20, shopCards[i].card.rect.x+81, shopCards[i].card.rect.y+240,255,255,255);
    }


    vector<relicId> copyRare(rareRelicPool.begin(), rareRelicPool.end());
    vector<relicId> copyCommon(commonRelicPool.begin(), commonRelicPool.end());
    vector<relicId> copyUncommon(uncommonRelicPool.begin(), uncommonRelicPool.end());
    for (int i{0}; i < 6; i++)
    {
        int seed = rand_int(0, 9);
        int costRand;
        set<relicId>* poolRand;
        vector<relicId>* copy;
        if (seed >= 0 && seed < 6)
        {
            costRand = rand_int(20, 28);
            poolRand = &commonRelicPool;
            copy = &copyCommon;            
        }
        else if (seed >= 6 && seed < 8) 
        {
            costRand = rand_int(38, 50);
            poolRand = &uncommonRelicPool;
            copy = &copyUncommon;
        }
        else                            
        {
            costRand = rand_int(56, 74);
            poolRand = &rareRelicPool;
            copy = &copyRare;
        }
        shuffle_vector(*copy);
        if (copy->size() == 0) shopRelics[i] = RelicItem(100, Relic(circlet));
        else
        {
            shopRelics[i] = RelicItem(costRand, Relic(copy->front()));
            cout << "generated relic id" << copy->front() << endl;
            copy->erase(copy->begin());
        }
        shopRelics[i].pool = poolRand;
        shopRelics[i].relic.move_rect(630+130*(i%3), 405+175*(i/3));
        shopRelics[i].costText = Text(20, shopRelics[i].relic.rect.x+15, shopRelics[i].relic.rect.y+80,255,255,255);
    }
}
