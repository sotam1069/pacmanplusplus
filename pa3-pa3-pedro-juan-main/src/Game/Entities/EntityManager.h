#pragma once

#include "BoundBlock.h"

class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> boundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);
	int getMapCoord(int row,int col) {return mapMatrix[row][col];}
    void setMapCord(int row, int col,int val) {mapMatrix[row][col] = val;}
	void UpdateGhostCoords();

private:
	bool killable = false;
	int killableCounter;
	int mapMatrix[40][40];
};