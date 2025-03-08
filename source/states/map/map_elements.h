#pragma once

#include <set>
#include <cstring>
#include "../../game.h"
#include "../../gui/gui.h"

extern Game game;

class Node : public Gui
{
    public:
        Node();
        Node(int pos_, int lev_);
        bool select();
        int pos;
        int lev;
        int id;
        enum nodeType {
            combat, shop, event
        };
        nodeType type;
        bool crossed{false};
        set<int> prev;
        set<int> next; 
};

class Tree
{
    public:
        Tree();
        void generate_path(int start);
        void nodes_process();
        void display();
        Node& cache_node(int pos, int lev);
        static vector<int> playerPath;
        static map<int, Node> nodeMap;
        static int playerCurrentLev;
};

