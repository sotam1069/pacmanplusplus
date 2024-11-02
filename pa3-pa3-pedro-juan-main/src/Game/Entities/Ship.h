#pragma once

#include "PowerUp.h"
#include "Entity.h"

class Ship : public Entity {

    private:
        bool isActive = false;
        int rank = 5;
        string name = "Ultimate";



    public:
        Ship(int x, int y, int width, int height, ofImage spriteSheet);
        void activate(int &num);
        void setIsActive(bool b) {isActive = b;}
        bool getIsActive() {return isActive;} 
        int getRank() {return rank;}
        string getName() {return name;}
        bool compareRank(PowerUp* p);
        void swap(int *xp, int *yp);

};