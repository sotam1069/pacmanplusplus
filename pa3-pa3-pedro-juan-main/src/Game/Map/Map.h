#pragma once

#include "Player.h"
#include "GhostSpawner.h"
#include "Whitepixel.h"


class Map{
    private:
      EntityManager *entityManager;
      Player* player;
      GhostSpawner* gs;

      vector<White*> RandomSpots;
      int mapMatrix[40][40];
    public:
      Map(EntityManager*);
      ~Map();
      void addBoundBlock(BoundBlock*);
      void addEntity(Entity*);
      Player* getPlayer();
      void setPlayer(Player*);
      void setGhostSpawner(GhostSpawner*);
      vector<Entity*> getEntities();
      void tick();
      void render();
      void keyPressed(int key);
		  void mousePressed(int x, int y, int button);
		  void keyReleased(int key);
      void addRandomSpot(White* w);
      White* getRandomSpot() {
        return RandomSpots[ofRandom(RandomSpots.size())];
      }
      void setMapCoord(int row,int column,int val) {mapMatrix[row][column] = val;}
      int getMapCoord(int row,int column) {return mapMatrix[row][column];}
      void UpdateEmCoords();
      EntityManager* getEntityManager() {return entityManager;}
};