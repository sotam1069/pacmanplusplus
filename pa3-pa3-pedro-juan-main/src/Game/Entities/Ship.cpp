#include "Ship.h"

Ship::Ship(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height) {
    sprite.cropFrom(spriteSheet,570,51,11,12);
}

void Ship::activate(int &num) {
    if (!isActive) {
         isActive = true;
    }
    else {isActive = false;}
}

bool Ship::compareRank(PowerUp* p) {

    if(this->getRank() > p->getRank()){
        return true;
    }
    else{ return false;}
}

void Ship::swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}