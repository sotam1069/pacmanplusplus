#pragma once

#include "Entity.h"

class BoundBlock: public Entity{
    public:
        BoundBlock(int, int, int, int, ofImage);
        ~BoundBlock();
};