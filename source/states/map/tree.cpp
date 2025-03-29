#include "map_elements.h"
// tach ra tu "map_elements.cpp"

Tree::Tree() {}

void Tree::renew()
{
    playerPath.clear(); nodeMap.clear();
    ironclad.currentLevel = 0; scrollVal = 0;
    cache_node(1, 0); cache_node(3, 0); cache_node(5, 0);
    generate_path(1);
    generate_path(3);
    generate_path(5);
}

Node& Tree::cache_node(int pos, int lev)
{
    int nodeId = lev*10+pos;
    if (nodeMap.find(nodeId) == nodeMap.end()) 
    {
        nodeMap[nodeId] = Node(pos, lev);
        return nodeMap[nodeId];
    }
    else return nodeMap.at(nodeId);
}

void Tree::generate_path(int start)
{
    int prevPos = start;
    for (int lev{1}; lev < BOSS_LEVEL; lev++)
    {
        int nextPos;
        if      (prevPos == 1) nextPos = rand_int(prevPos  , prevPos+1); 
        else if (prevPos == 5) nextPos = rand_int(prevPos-1, prevPos);
        else                   nextPos = rand_int(prevPos-1, prevPos+1);
        Node& cached = cache_node(nextPos, lev);
        if (lev == BOSS_LEVEL-1) cached.type = Node::nodeType::rest;
        else if (lev == 10)      cached.type = Node::nodeType::elite;
        else                     cached.rand_type();
        cached.prev.insert((lev-1)*10+prevPos);
        nodeMap.find((lev-1)*10+prevPos)->second.next.insert(cached.id);
        prevPos = nextPos;
        if (lev == BOSS_LEVEL-1)
        {
            Node& boss = cache_node(3, BOSS_LEVEL);
            boss.rect = {boss.rect.x-51, boss.rect.y, 350, 350};
            boss.type = Node::nodeType::boss;
            cached.next.insert(boss.id);
            nodeMap.find(boss.id)->second.prev.insert(cached.id);
        }
    }
}

void draw_thick_line(int x1, int y1, int x2, int y2)
{
    for (int i{-2}; i <= 2; i++)
    {
        SDL_RenderDrawLine(game.renderer, x1+i, y1, x2+i, y2); //fix to make diagonals look better 
    }
}

void Tree::display()
{
    if (!panel.inMenu) scroll_val(scrollVal, 0, 1200);
    for (const auto& node:nodeMap)
    {
        for (const auto& next:node.second.next) draw_thick_line(30+node.second.rect.x, 30+NODE_POS_Y_DEFAULT+NODE_Y_STEP_INCREMENT*node.second.lev+scrollVal, 300+150*(next%10), NODE_POS_Y_DEFAULT+30+NODE_Y_STEP_INCREMENT*(next/10)+scrollVal);
    }
    for (auto& node:nodeMap) 
    {   
        int alpha;
        if (!(node.second.lev == ironclad.currentLevel && (playerPath.size() == 0 || node.second.prev.find(playerPath.back()) != node.second.prev.end()))) alpha = 80;
        else alpha = 255;
        if (node.second.lev == 20) node.second.rect.y = NODE_POS_Y_DEFAULT+NODE_Y_STEP_INCREMENT*node.second.lev-250+scrollVal;
        else node.second.rect.y = NODE_POS_Y_DEFAULT+NODE_Y_STEP_INCREMENT*node.second.lev+scrollVal;
        switch (node.second.type)
        {
            case (node.second.combat):
            {
                game.render_img("assets/map/monster.png", node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
            case (node.second.rest):
            {
                game.render_img("assets/map/rest.png"    , node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
            case (node.second.event):
            {
                game.render_img("assets/map/event.png"   , node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
            case (node.second.shop):
            {
                game.render_img("assets/map/shop.png"    , node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
            case (node.second.treasure):
            {
                game.render_img("assets/map/treasure.png", node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
            case (node.second.elite):
            {
                game.render_img("assets/map/elite.png"   , node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
            case (node.second.boss):
            {
                game.render_img("assets/map/boss.png"    , node.second.rect.x, node.second.rect.y, node.second.rect.w, node.second.rect.h, alpha, NULL);
                break;
            }
        }
    }
    if (!panel.inMenu) scrollDirection = SCROLL_NULL;
}

void Tree::nodes_process()
{
    display();
    for (auto node:nodeMap)
    {
        if (node.second.lev == ironclad.currentLevel && (playerPath.size() == 0 || node.second.prev.find(playerPath.back()) != node.second.prev.end())) 
        {
            if (!panel.inMenu && node.second.select()) 
            {
                if (ironclad.currentLevel > 0) cout << playerPath.back() << " to " << node.second.id << endl;
                playerPath.push_back(node.second.id);
                ironclad.currentLevel++;
            }
        }
    }
}
