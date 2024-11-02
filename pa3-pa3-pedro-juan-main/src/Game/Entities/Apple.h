#pragma once

#include <Entity.h>

class Apple : public Entity {

    public:
        Apple(int x, int y, int width, int height, ofImage spriteSheet);
};