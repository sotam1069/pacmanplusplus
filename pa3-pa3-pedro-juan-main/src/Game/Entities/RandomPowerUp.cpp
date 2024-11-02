#include "RandomPowerUp.h"
#include "PowerUp.h"

void RandomPowerUp::activate(int &num) {
    if (!isActive) {
        isActive = true;
    }
    else {
        isActive = false;
        num = num + (rand() % 1000);
    }
}

bool RandomPowerUp::compareRank(PowerUp* p){

    if(this->getRank() > p->getRank()){
        return true;
    }
    else{ return false;}
}