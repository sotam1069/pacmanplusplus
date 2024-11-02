#include "Bell.h"

Bell::Bell(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height) {
    sprite.cropFrom(spriteSheet,586,50,11,12);
}

