#pragma once

#include "EntityManager.h"
#include "Entity.h"
#include "GhostSpawner.h"

class Eyes : public Entity{

    public:
        Eyes(int, int, int, int,EntityManager*, ofImage, GhostSpawner*);
        void tick();        
        void setPositions(vector<tuple<int,int>> v) {positions = v;}
            
    private:
        bool dead = false;
        bool killable = false;
        bool canMove = true;
        EntityManager* em;
        vector<tuple<int,int>> positions;
        GhostSpawner* gs;
        string ghostColors[4] = {"red","pink","cyan", "orange"};

};