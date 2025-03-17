#include "shop.h"

void Game::display_shop()
{
    game.render_img("assets/scene/shop_rug.png",0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    static ReturnButton rtButton;
    static Shop shop;
    if (game.shopInit)
    {
        deck.set_up_piles(false);
        srand(time(NULL));
        shop.generate_items();
        shop.rsButton.used = false;
        game.shopInit = false;
    }
    rtButton.process();
    shop.process();
    panel.display();
}

Shop::Shop() {}
void Shop::process()
{
    if (!rsButton.active) purchase_process();
    display_items();
    rsButton.process();
}
void Shop::display_items()
{
    bool toHighlight = !(rsButton.active);
    for (auto cardItem:shopCards)
    {
        cardItem.card.display_copy(cardItem.card.rect.x, cardItem.card.rect.y, true, toHighlight);
        cardItem.costText.render_text(to_string(cardItem.cost));
        game.render_img("assets/ui/gold.png", cardItem.card.rect.x+43, cardItem.card.rect.y+232, 40, 40, 255, NULL);
    }
    for (auto relicItem:shopRelics)
    {
        relicItem.relic.display();
        relicItem.costText.render_text(to_string(relicItem.cost));
        game.render_img("assets/ui/gold.png", relicItem.relic.rect.x-3, relicItem.relic.rect.y+72, 40, 40, 255, NULL);
    }
}
void Shop::purchase_process()
{
    for (int i{shopCards.size()-1}; i >= 0; i--)
    {
        if (shopCards[i].cost <= ironclad.gold && shopCards[i].card.detect_click()) 
        {
            ironclad.cardIdInv.push_back(shopCards[i].card.id);
            ironclad.gold -= shopCards[i].cost;
            shopCards.erase(shopCards.begin()+i);
        }
    }
    for (int i{shopRelics.size()-1}; i >= 0; i--)
    {
        if (shopRelics[i].cost <= ironclad.gold && shopRelics[i].relic.detect_click()) 
        {
            ironclad.relicInv.push_back(Relic(shopRelics[i].relic.id)); //written weirdly so that new relic elems have correct rect
            ironclad.gold -= shopRelics[i].cost;
            if (shopRelics[i].relic.id != circlet) shopRelics[i].pool->erase(shopRelics[i].relic.id);
            shopRelics.erase(shopRelics.begin()+i);
        }
    }
}


ReturnButton::ReturnButton() : Gui(0, 710, 270, 90) {}

void ReturnButton::display()
{
    game.render_img("assets/ui/return_button.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

void ReturnButton::process()
{
    display();
    if (detect_click()) 
    {
        game.shopInit = true;
        game.state_switch(Game::gameStates::map);
    }
}

int RemovalService::cost{75};
RemovalService::RemovalService() : Gui(1050, 415, 200, 280) {}
void RemovalService::display()
{
    Uint8 alpha;
    if (used) alpha = 80;
    else alpha = 255;
    game.render_img("assets/ui/removal_service.png", rect.x, rect.y, rect.w, rect.h, alpha, NULL);
    game.render_img("assets/ui/gold.png", rect.x+56, rect.y+272, 40, 40, 255, NULL);
    costText.render_text(to_string(cost));
}

void RemovalService::process()
{
    display();
    if (!used && ironclad.gold >= cost && (active || detect_click())) 
    {
        active = true;
        deck.display_pile(deck.drawPile, 3, true);
        int chosen = deck.interact_cards_event(); 
        if (chosen != NULL_CARD)
        {
            ironclad.cardIdInv.erase(ironclad.cardIdInv.begin()+chosen);
            ironclad.gold -= cost;
            active = false;
            used = true;
        }
    }
}
