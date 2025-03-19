#include "event.h"

void Game::display_event()
{
    static Event event;
    if (eventInit)
    {
        deck.renew_inventory();
        event.generate();
        for (auto& choice:event.attributes.choices) choice.currentUses = choice.attributes.uses;
        eventInit = false;
    }
    
    render_img("assets/scene/def_background.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    render_img("assets/events/panel.png", 50, 150, 1380, 650, 255, NULL);
    event.process();

    panel.display();
}

static vector<eventId> eventIdList = {bf_spirits, duplicator}; //duplicator, bf_spirits
bool Event::inMenu = false;
Event::Event() {}

void Event::generate()
{
    shuffle_vector(eventIdList);
    id = eventIdList.back();
    attributes = evAttriMap.at(id);
    complete = false;
}

void Event::process()
{
    game.render_img(attributes.imgName.c_str(), 100, 272, 480, 480, 255, NULL);
    title.render_text(attributes.titleText);
    desc.render_text(attributes.descText);
    if (!complete)
    {
        for (Choice& choice:attributes.choices) 
        {
            if (attributes.unique) { if (choice.process()) complete = true; }
            else choice.process();
        }
    }
    if (complete) attributes.choices.back().process();
}


Choice::Choice(choiceId id_, int pos_) : Gui(616, 622+80*pos_, 760, 50) 
{
    id = id_;
    pos = pos_;
    attributes = choiceAttriMap.at(id);
    currentUses = attributes.uses;
}

void Choice::display()
{
    game.render_img("assets/events/enabled_button.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
    label.render_text(attributes.label);
}

bool Choice::process()
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
            return true;
        } 
    }
    return false;
}
