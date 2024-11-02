#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "DoubleSpeed.h"
#include "RandomPowerUp.h"
#include "Cherry.h"
#include "Ship.h"

enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity {

    private:
        int spawnX, spawnY;
        int RandX, RandY;
        unsigned int health = 3;
        int score=0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;
        bool hasUpdated = false;
        int pixelMultiplier = 16;
        ofImage MapImage;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        DoubleSpeed SpeedBoost;
        RandomPowerUp random;
        string path;
        int EatCount = 0;
        bool isInvencible = false;
        bool isInvis = false;
        bool gpsActive = false;
        int steps = 0;
        vector<PowerUp*> collectedPowerUps;
        ofImage spriteSheet;
        vector<ofRectangle> GPSsquares;
        string Path;
        ofRectangle PacmanHitBox;

    public:
        Player(int, int, int , int, EntityManager*, bool);
        ~Player();
        int getHealth();
        int getScore();
        FACING getFacing();
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();
        int  getEatCount() {return EatCount;}
        void setEatCount(int n) {EatCount = n;}
        void swap(PowerUp* a, PowerUp* b);
        void UpdateCoords();
        void GPS(string path);
        void revertGPS();
        string GPSPath(int x,int y);
        int convertToCoordsX(int num);
        int convertToCoordsY(int num);
        int convertToXPos(int cord);
        int convertToYPos(int cord);
};