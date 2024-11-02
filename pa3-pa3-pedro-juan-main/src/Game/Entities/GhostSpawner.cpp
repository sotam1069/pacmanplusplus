#include "GhostSpawner.h"
#include "Ghost.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(){
    std::vector<string> colors;
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");
    if (justStarted) {
        if(em->ghosts.size()<4){
            if(spawnCounter == 0){
                spawnGhost(colors[ofRandom(4)]);
                spawnCounter = 30*5;
            }else{
                spawnCounter--;
            }
        }
        if (em->ghosts.size() == 4) {justStarted = false;}
    }
}
void GhostSpawner::spawnGhost(string color){
    Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
    g->setGhostSpawner(this);
    em->ghosts.push_back(g);
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        spawnGhost(ghostColors[int(ofRandom(4))]);
    }
}