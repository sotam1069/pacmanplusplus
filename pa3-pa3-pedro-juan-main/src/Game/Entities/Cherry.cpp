#include "Cherry.h"

Cherry::Cherry(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x,y,width,height) {
    sprite.cropFrom(spriteSheet,490,49,11,12);

}

void Cherry::activate(int &num) {
    if (!isActive) {
         isActive = true;
    }
    else {isActive = false;}
}

bool Cherry::compareRank(PowerUp* p){

    if(this->getRank() > p->getRank()){
        return true;
    }
    else{ return false;}
}
