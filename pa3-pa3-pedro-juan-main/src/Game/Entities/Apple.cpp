#include "Apple.h"

Apple::Apple(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height) {
    sprite.cropFrom(spriteSheet,538,50,11,12);
}

