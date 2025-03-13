#include "map_elements.h"
// tach ra tu "map_elements.cpp"

int Tree::playerCurrentLev{0};
map<int, Node> Tree::nodeMap;
vector<int> Tree::playerPath = {};
Tree::Tree()
{
    srand(time(NULL));
    cache_node(1, 0); cache_node(3, 0); cache_node(5, 0);
    generate_path(1);
    generate_path(3);
    generate_path(3);
    generate_path(5);
}

Node& Tree::cache_node(int pos, int lev)
{
    int nodeId = pos*10+lev;
    auto it = nodeMap.find(nodeId);
    if (it == nodeMap.end()) 
    {
        nodeMap[nodeId] = Node(pos, lev);
        return nodeMap[nodeId];
    }
    else return (it->second);
}

void Tree::generate_path(int start)
{
    int prev = start;
    for (int lev{1}; lev < 10; lev++)
    {
        int next;
        if      (prev == 1) next = rand() % 2+prev; 
        else if (prev == 5) next = rand() % 2+(prev-1);
        else                next = rand() % 3+(prev-1);
        Node& cached = cache_node(next, lev);
        cached.rand_type();
        cached.prev.insert(prev*10+lev-1);
        nodeMap.find(prev*10+lev-1)->second.next.insert(next*10+lev);
        prev = next;
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
    for (auto node:nodeMap)
    {
        for (auto next:node.second.next) draw_thick_line(30+node.second.rect.x, 30+node.second.rect.y, 300+150*(next/10), 780-80*(next%10));
    }
    for (auto node:nodeMap) 
    {   
        int alpha;
        if (!(node.second.lev == playerCurrentLev && (playerPath.size() == 0 || node.second.prev.find(playerPath.back()) != node.second.prev.end()))) alpha = 100;
        else alpha = 255;
        switch (node.second.type)
        {
            case (node.second.combat):
            {
                game.render_img("assets/map/monster.png", node.second.rect.x, node.second.rect.y, 60, 60, alpha, NULL);
                break;
            }
            case (node.second.rest):
            {
                game.render_img("assets/map/rest.png", node.second.rect.x, node.second.rect.y, 60, 60, alpha, NULL);
                break;
            }
            case (node.second.event):
            {
                game.render_img("assets/map/event.png", node.second.rect.x, node.second.rect.y, 60, 60, alpha, NULL);
                break;
            }
        }
    }
}

void Tree::nodes_process()
{
    display();
    for (auto node:nodeMap)
    {
        if (node.second.lev == playerCurrentLev && (playerPath.size() == 0 || node.second.prev.find(playerPath.back()) != node.second.prev.end())) 
        {
            if (node.second.select()) 
            {
                if (playerCurrentLev > 0) cout << playerPath.back() << " to " << node.second.id << endl;
                playerPath.push_back(node.second.id);
                playerCurrentLev++;
            }
        }
    }
}
