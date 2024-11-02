#pragma once

#include "ofMain.h"

enum FACING {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Entity {
	protected:
		int x, y, width, height, health;
		ofImage sprite;
		int ticks = 0;
		int mapMatrix[40][40];
	public:
		explicit Entity(int x, int y, int width, int height);
		virtual ~Entity();
		virtual void tick();
		virtual void render();
		bool remove = false;
		void damage(Entity* damageSource);
		bool collides(Entity* entity);
		int getX() {return x;}
		int getY() {return y;}
		ofRectangle getBounds();
		ofRectangle getBounds(int x, int y);
		int getMapCoord(int row,int col) {return mapMatrix[row][col];}
        void setMapCord(int row, int col,int val) {mapMatrix[row][col] = val;}
};