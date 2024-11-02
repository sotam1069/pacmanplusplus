#pragma once

#include "PowerUp.h"
#include "Entity.h"

class Strawberry : public PowerUp, public Entity {
    private: 
        int steps;
        bool isInvisible;
        bool isActive = false;
        int rank = 2;
        string name = "Invisibility";
    
    public:
        void activate(int &num);
        bool getIsInvisible() {return isInvisible;}
        void setIsInvisible(bool b) {isInvisible = b;}
        int getSteps() {return steps;}
        void setSteps(int n) {steps = n;}
        Strawberry(int x, int y, int width, int height, ofImage spriteSheet);
        void setIsActive(bool b) {isActive = b;}
        bool getIsActive() {return isActive;} 
        int getRank() {return rank;}
        string getName() {return name;}
        bool compareRank(PowerUp* p);
};