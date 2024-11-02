#pragma once
#include "PowerUp.h"
class DoubleSpeed : public PowerUp {
    private:
        bool isActive = false;
        int rank = 3;
        string name = "2x Speed";
    public:
        void activate(int &num);
        bool getIsActive() {return isActive;}
        void setIsActive(bool b) {isActive = b;}
        int getRank() {return rank;}
        string getName() {return name;}
        bool compareRank(PowerUp* p);
};