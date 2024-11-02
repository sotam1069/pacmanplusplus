#pragma once

#include "EntityManager.h"
#include "Animation.h"
#include "Eyes.h"
#include "Map.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);
        int convertToCoordsX(int num);
        int convertToCoordsY(int num);
        void UpdateCoords();
        int convertToXPos(int cord);
        int convertToYPos(int cord);
        void setDead(bool b);
        bool getDead();
        vector<tuple<int,int>> getPositions() {return positions;}
        EntityManager* getEM() {return em;}
        void setGhostSpawner(GhostSpawner* g) {gs = g;}
        GhostSpawner* getGS() {return gs;}

    private:
        bool killable = false;
        bool dead = false;
        int MatrixX = 19;
        int MatrixY = 19;
        ofImage MapImage;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=2;
        EntityManager* em;
        Animation* killableAnim;
        Map* map;
        ofImage spriteSheet;
        int pixelMultiplier;
        bool hasUpdated = false;
        vector<tuple<int,int>> positions;
        GhostSpawner* gs;

};