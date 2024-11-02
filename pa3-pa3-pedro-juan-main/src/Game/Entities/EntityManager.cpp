#include "EntityManager.h"
#include "Ghost.h"
#include "Cherry.h"
#include "Strawberry.h"
#include "GreenFruit.h"
#include "Orange.h"
#include "Apple.h"
#include "Ship.h"
#include "Bell.h"
#include "Whitepixel.h"

void EntityManager::tick(){
    if(killable){
        killableCounter--;
        if (killableCounter == 0){
            killable = false;
            for(Entity* entity:ghosts){
                Ghost* ghost = dynamic_cast<Ghost*>(entity); 
                ghost->setKillable(false);
            }
        }
    }
    std::vector<int> toRemove;
    
    for(unsigned int i=0;i<entities.size();i++){
        if(!entities[i]->remove){
            entities[i]->tick();

        }else{
            toRemove.push_back(i);
        }
    }
    for(unsigned int removable: toRemove){
        Entity* entityPointer = entities[removable];
        entities.erase(entities.begin() + removable);
        delete entityPointer;
    }
    toRemove.clear();
    for(BoundBlock* BoundBlock: boundBlocks){
        BoundBlock->tick();
    }
    for(unsigned int i=0;i<ghosts.size();i++){
        if(!ghosts[i]->remove){
            ghosts[i]->tick();

        }else{
            toRemove.push_back(i);
        }
    }
    for(unsigned int removable: toRemove){
        Ghost* entityPointer = dynamic_cast<Ghost*>(ghosts[removable]);
        ghosts.erase(ghosts.begin() + removable);
        delete entityPointer;
    }
}

void EntityManager::render(){
    for(Entity* entity: entities){
        entity->render();
    }
    for(BoundBlock* BoundBlock: boundBlocks){
        BoundBlock->render();
    }
    for(Entity* ghost: ghosts){
        ghost->render();
    }
}

void EntityManager::setKillable(bool k){
    killable = true;
    killableCounter=30*10;
    for(Entity* entity:ghosts){
        Ghost* ghost = dynamic_cast<Ghost*>(entity); 
        ghost->setKillable(true);
    }
}

EntityManager::~EntityManager(){
    for(Entity* e: boundBlocks) delete dynamic_cast<BoundBlock*>(e);

    for(Entity* e: ghosts) delete dynamic_cast<Ghost*>(e);

    for(Entity* e: entities) delete e;
    
    boundBlocks.clear();
    ghosts.clear();
    entities.clear();
}

void EntityManager::UpdateGhostCoords() {
    for (Entity* g : ghosts) {
        for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 40; j++) {
                g->setMapCord(j,i,this->getMapCoord(j,i));
            }
        }
    }
}


