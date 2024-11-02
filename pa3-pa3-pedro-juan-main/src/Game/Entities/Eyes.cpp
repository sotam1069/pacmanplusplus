#include "Eyes.h"
#include "BoundBlock.h"
#include "GhostSpawner.h"

Eyes::Eyes(int x, int y, int width, int height,EntityManager* em, ofImage spriteSheet,GhostSpawner* gs) : Entity(x,y,width,height){
    this->em = em;
    this->gs = gs;
    sprite.cropFrom(spriteSheet,602,84,10,5);
}


void Eyes::tick() {
    if (positions.size() == 0) {
        gs->spawnGhost(ghostColors[int(ofRandom(4))]);
        this->remove = true;
    }
    else { 
    x = get<0>(positions[positions.size()]);
    y = get<1>(positions[positions.size()]);
    positions.pop_back();
    }
}



