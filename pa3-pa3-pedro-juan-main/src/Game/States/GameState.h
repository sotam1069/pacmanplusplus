#pragma once

#include "State.h"
#include "Player.h"
#include "MapBuilder.h"
#include "Ship.h"
#include "EntityManager.h"
#include "Whitepixel.h"
#include "Eyes.h"
#include "Ghost.h"

class GameState: public State{
    public: 
        GameState();
		~GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		int getFinalScore();
		Map * getMap() {return map;}
		void setIsMsPacman(bool b) {isMsPacman = b;}
		bool getIsMsPacman() {return isMsPacman;}

	
	private:
		ofSoundPlayer music;
		ofImage mapImage;
		ofImage spriteSheet;
		Map *map;
		Ghost* ghost;
		Ship *ship;
		EntityManager* em;
		Entity* entity;
		
		int finalScore=0;
		int Dots;
		bool isMsPacman = false;
		int counter = 0;

};