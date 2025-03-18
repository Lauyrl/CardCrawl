#include "event.h"

void Game::display_event()
{
    static Event teste;
    if (eventInit)
    {
        deck.renew_inventory();
        for (auto& choice:teste.attributes.choices) choice.currentUses = choice.attributes.uses;
        eventInit = false;
    }
    
    render_img("assets/scene/def_background.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    render_img("assets/events/panel.png", 50, 150, 1380, 650, 255, NULL);
    teste.process();

    panel.display();
}

static vector<eventId> eventIdList = {duplicator};
bool Event::inMenu = false;
Event::Event()
{
    shuffle_vector(eventIdList);
    id = eventIdList.back();
    attributes = evAttriMap.at(id);
}

void Event::process()
{
    game.render_img(attributes.imgName.c_str(), 100, 260, 480, 480, 255, NULL);
    title.render_text(attributes.titleText);
    desc.render_text(attributes.descText);
    for (Choice& choice:attributes.choices) choice.process();
}


Choice::Choice(choiceId id_, int pos_) : Gui(580, 500+100*pos_, 800, 50) 
{
    id = id_;
    pos = pos_;
    attributes = choiceAttriMap.at(id);
    currentUses = attributes.uses;
}

void Choice::display()
{
    game.render_img("assets/ui/event/enabled_button.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
    label.render_text(attributes.label);
}

void Choice::process()
{
    if (currentUses > 0 && !Event::inMenu)
    {
        display();
        if (!panel.inMenu && detect_click()) 
        {
            Event::inMenu = true;
            cursorX = 0; cursorY = 0;
            currentUses--;
            chosen = true; 
        } 
    }
    if (chosen) 
    {
        if (attributes.effect()) 
        {
            chosen = false;
            Event::inMenu = false;
        } 
    }
}
