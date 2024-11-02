#include "Strawberry.h"

Strawberry::Strawberry(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height) {
    sprite.cropFrom(spriteSheet,506,50,11,12);
}


void Strawberry::activate(int &num) {
    if (!isActive) {
         isActive = true;
    }
    else {isActive = false;}
}

bool Strawberry::compareRank(PowerUp* p) {

    if(this->getRank() > p->getRank()){
        return true;
    }
    else{ return false;}
}


