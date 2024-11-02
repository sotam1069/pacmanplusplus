#include "BigDot.h"

BigDot::BigDot(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 643,18,16,16);
}