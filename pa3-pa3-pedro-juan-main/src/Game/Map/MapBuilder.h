#pragma once

#include "ofMain.h" 
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "Cherry.h"
#include "Strawberry.h"
#include "GreenFruit.h"
#include "Orange.h"
#include "Apple.h"
#include "Ship.h"
#include "Bell.h"
#include "Whitepixel.h"

class MapBuilder {
    public:
        MapBuilder();
	Map* createMap(ofImage , bool IsMsPacman);
        int getDotCount(ofImage);
        
	private:
        vector<ofImage> bound;
        int pixelMultiplier;
        ofColor boundBoundBlock;
        ofColor pacman;
        ofColor ghostC;
	ofColor dotC;
	ofColor bigDotC;
        ofColor StrawberryC;
        ofColor CherryC;
        ofColor GreenFruitC;
        ofColor OrangeC;
        ofColor AppleC;
        ofColor ShipC;
        ofColor BellC;
        ofImage pacmanSpriteSheet;
        ofImage tempBound;
        ofColor whiteC;
        ofImage getSprite(ofImage, int, int);
        EntityManager* entityManager;
        Entity* entity;
};