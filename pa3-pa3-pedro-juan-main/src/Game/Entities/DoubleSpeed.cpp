#include "DoubleSpeed.h"

void DoubleSpeed::activate(int &num) {
    if (!isActive) {
        num = num * 2;
        isActive = true;
    }
    else {
        isActive = false;
        num = 4;
    }
}

bool DoubleSpeed::compareRank(PowerUp* p) {

    if(this->getRank() > p->getRank()){
        return true;
    }
    else{ return false;}
}