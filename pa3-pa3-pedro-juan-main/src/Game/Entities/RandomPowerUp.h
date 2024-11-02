#pragma once
#include "PowerUp.h"
class RandomPowerUp : public PowerUp {
    private:
        int rank = 5;
        bool isActive = false;
        string name = "RandomPowerUp";
    public:
        void activate(int &num);
        bool getIsActive() {return isActive;}
        void setIsActive(bool b) {isActive = b;}
        int getRank() {return rank;}
        bool compareRank(PowerUp* p);
        string getName() {return name;}
};