#include "GreenFruit.h"

GreenFruit::GreenFruit(int x, int y, int width, int height, ofImage spriteSheet) : Entity(x, y, width, height) {
    sprite.cropFrom(spriteSheet,555,49,11,12);
}

