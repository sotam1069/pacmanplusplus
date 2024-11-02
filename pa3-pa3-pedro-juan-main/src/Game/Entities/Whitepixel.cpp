#include "Whitepixel.h"

White::White(int x, int y, int width, int height, ofImage sprite): Entity(x, y, width, height){
    this->sprite = sprite;
}