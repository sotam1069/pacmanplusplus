#include "BoundBlock.h"

BoundBlock::BoundBlock(int x, int y, int width, int height, ofImage sprite): Entity(x, y, width, height){
    this->sprite=sprite;
}
BoundBlock::~BoundBlock(){}