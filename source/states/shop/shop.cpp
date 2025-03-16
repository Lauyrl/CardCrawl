#include "shop.h"

void Game::display_shop()
{
    game.render_img("assets/scene/shop_rug.png",0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    static Shop shop;
    static ReturnButton rtButton;
    if (game.shopInit)
    {
        shop.generate_items();
        game.shopInit = false;
    }
    shop.process();
    rtButton.process();
    panel.display();
}

vector<cardIdInv> Shop::cardIds = {strike, defend, iron_wave};
vector<relicId> Shop::relicIds = {anchor, blood_vial};
Shop::Shop() {}
void Shop::process()
{
    display_items();
    purchase_process();
}
void Shop::generate_items()
{
    shopCards.clear(); shopRelics.clear();
    shuffle_vector(cardIds);
    for (int i{cardIds.size()-1}; i >= 0; i--)
    {
        shopCards.push_back(CardItem(20, Card(cardIds[i], i)));
        shopCards.back().card.move_rect(200+200*i, 200);
        shopCards.back().costText = Text(20, shopCards.back().card.rect.x+80, shopCards.back().card.rect.y+240,255,255,255);
    }
    shuffle_vector(relicIds);
    for (int i{relicIds.size()-1}; i >= 0; i--)
    {
        shopRelics.push_back(RelicItem(20, Relic(relicIds[i])));
        shopRelics.back().relic.move_rect(240+200*i, 500);
        shopRelics.back().costText = Text(20, shopRelics.back().relic.rect.x+37, shopRelics.back().relic.rect.y+80,255,255,255);
    }
}
void Shop::display_items()
{
    for (auto cardItem:shopCards)
    {
        cardItem.card.display_copy(cardItem.card.rect.x, cardItem.card.rect.y, true);
        cardItem.costText.render_text(to_string(cardItem.cost));
        game.render_img("assets/ui/gold.png", cardItem.card.rect.x+42, cardItem.card.rect.y+232, 40, 40, 255, NULL);
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
            ironclad.relicInv.push_back(Relic(shopRelics[i].relic.id));
            ironclad.gold -= shopCards[i].cost;
            shopRelics.erase(shopRelics.begin()+i);
        }
    }
}

ReturnButton::ReturnButton() : Gui(0, 600, 270, 90)
{}

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
