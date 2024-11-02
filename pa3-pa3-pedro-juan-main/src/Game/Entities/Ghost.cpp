#include "Ghost.h"
#include "BoundBlock.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color) : Entity(x, y, width, height){
    this->em = em;
    MapImage.load("images/map1.png");
    pixelMultiplier = 16;
    spriteSheet.load("images/Background.png");
    vector<ofImage> killableFrames;
    ofImage temp;
    temp.cropFrom(spriteSheet, 584, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 64, 16, 16);
    killableFrames.push_back(temp);    
    temp.cropFrom(spriteSheet, 632, 64, 16, 16);
    killableFrames.push_back(temp);
    killableAnim = new Animation(10, killableFrames);

    if(color == "red")      sprite.cropFrom(spriteSheet,456,64,16,16);
    else if(color=="pink")  sprite.cropFrom(spriteSheet,456,78,16,16);
    else if(color=="cyan")  sprite.cropFrom(spriteSheet,456,96,16,16);
    else if(color=="orange")sprite.cropFrom(spriteSheet,456,113,16,16);
}

void Ghost::tick(){
    if (!hasUpdated) {
        UpdateCoords();
    }
    killableAnim->tick();
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
        }else if(facing == DOWN){
            y+=speed;
        }else if(facing == LEFT){
            x-=speed;
        }else if(facing == RIGHT){
            x+=speed;
        }
        positions.push_back(make_tuple(x,y));
        if (convertToCoordsX(x) != MatrixX || convertToCoordsY(y) != MatrixY) {
            MatrixX = convertToCoordsX(x);
            MatrixY = convertToCoordsY(y)+1;
            if (getMapCoord(MatrixY,MatrixX) != 5 && getMapCoord(MatrixY,MatrixX) != 1) {
               setMapCord(MatrixY,MatrixX,1); 
            }
        }
    }else{
        int randInt;
        if(justSpawned){
            randInt = ofRandom(2);

        }else{
            randInt = ofRandom(4);
        }
        if(randInt == 0){
            facing = LEFT;
        }else if(randInt == 1){
            facing = RIGHT;
        }else if(randInt == 2){
            facing = DOWN;
        }else if(randInt == 3){
            facing = UP;
        }
        justSpawned = false;

    }

}

void Ghost::render(){
    if(killable){
        killableAnim->getCurrentFrame().draw(x,y,width,height);
    }else if (dead) {
        killable = false;
        
        // returnToSpawn();
    }else{
        Entity::render();
    }
}

bool Ghost::getKillable(){
    return killable;
}
void Ghost::setKillable(bool k){
    killable = k;
}
void Ghost::checkCollisions(){
    for(BoundBlock* BoundBlock: em->boundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
}

Ghost::~Ghost(){
    delete killableAnim;
}

int Ghost::convertToCoordsX(int num) {
    int Offset = (ofGetWidth() - MapImage.getHeight()*16)/2;
    int out = (num - Offset) / pixelMultiplier; 
    return out;
}

int Ghost::convertToCoordsY(int num) {
    int Offset = (ofGetHeight() - MapImage.getWidth()*16)/2;
    return (num - Offset) / pixelMultiplier;
}

void Ghost::UpdateCoords() {
     for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 40; j++) {
                this->setMapCord(j,i,em->getMapCoord(j,i));
            }
        }
        hasUpdated = true;
}

int Ghost::convertToYPos(int cord) {
     int Offset = (ofGetHeight() - MapImage.getWidth()*16)/2;
     return cord * pixelMultiplier + Offset;
}

int Ghost::convertToXPos(int cord) {
    int Offset = (ofGetWidth() - MapImage.getHeight()*16)/2;
    return cord * pixelMultiplier + Offset;
}

void Ghost::setDead(bool b) {dead = b;}
bool Ghost::getDead() {return dead;}

// void Ghost::returnToSpawn() {
//     int Ix = MatrixX;
//     int Iy = MatrixY;
//     if (getMapCoord(Iy - 1,Ix) == 5 || getMapCoord(Iy + 1,Ix) == 5|| getMapCoord(Iy,Ix - 1) == 5 || getMapCoord(Iy,Ix + 1) == 5) {
//         dead = false;
//         return;
//     }
//     if (getMapCoord(Iy - 1,Ix) == 1) {
//         x = convertToCoordsX(Ix);
//         y = convertToCoordsY(Iy - 1);
//         MatrixX = Ix;
//         MatrixY = Iy;
//         returnToSpawn();
//     }if (getMapCoord(Iy + 1,Ix) == 1) {
//         x = convertToCoordsX(Ix);
//         y = convertToCoordsY(Iy + 1);
//         MatrixX = Ix;
//         MatrixY = Iy;
//         returnToSpawn();
//     }if (getMapCoord(Iy,Ix - 1) == 1) {
//         x = convertToCoordsX(Ix - 1);
//         y = convertToCoordsY(Iy);
//         MatrixX = Ix;
//         MatrixY = Iy;
//         returnToSpawn();
//     }if (getMapCoord(Iy,Ix + 1) == 1) {
//         x = convertToCoordsX(Ix + 1);
//         y = convertToCoordsY(Iy);
//         MatrixX = Ix;
//         MatrixY = Iy;
//         returnToSpawn();
//     } 

// }


