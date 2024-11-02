#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "Cherry.h"
#include "Strawberry.h"
#include "GreenFruit.h"
#include "Orange.h"
#include "Apple.h"
#include "Ship.h"
#include "Bell.h"
#include "Whitepixel.h"

Player::Player(int x, int y, int width, int height, EntityManager* em , bool isMsPacman) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    PacmanHitBox.setHeight(10);
    PacmanHitBox.setWidth(10);
    MapImage.load("images/map1.png");
    if (isMsPacman) {
        sprite.load("images/mspacman.png");
    } else {sprite.load("images/pacman.png");}
     
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;
    moving = MLEFT;
    spriteSheet.load("images/Background.png");

    
}

void Player::tick(){
    PacmanHitBox.setPosition(x,y);
    if (gpsActive) {
        GPS(GPSPath(convertToCoordsY(y),convertToCoordsX(x)));
    }
    if (!hasUpdated) {
        UpdateCoords();
    }
    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-=speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }
    if (isInvencible) {
        steps += 1;
    }
    if (steps >= 50) {
        steps = 0;
        isInvencible = false;
        isInvis = false;
    }
}

void Player::render(){
    if (gpsActive && GPSsquares.size() != 0) {
        ofSetColor(255,0,0,64);
        ofFill();
        for (ofRectangle r : GPSsquares) {
            ofDrawRectangle(r);
        }
        revertGPS();
    }
    if (!isInvis) {
       ofSetColor(256,256,256); 
    }
    if (isInvis) {
        ofSetColor(256,256,256,64);
    } 
    // ofDrawRectangle(getBounds());
    if(facing == UP)
        walkUp->getCurrentFrame().draw(x, y, width, height);
    else if(facing == DOWN)
        walkDown->getCurrentFrame().draw(x, y, width, height);
    else if(facing == LEFT)
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    else if(facing == RIGHT)
        walkRight->getCurrentFrame().draw(x, y, width, height);
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);
    ofDrawBitmapString("Power Ups:", ofGetWidth() / 4 - 100, ofGetHeight() - 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
    if (collectedPowerUps.size() > 0) {
        for (unsigned int i = 0; i < collectedPowerUps.size(); i++) {
            ofDrawBitmapString(collectedPowerUps[i]->getName() + ", ", ofGetWidth() / 4 + 110 * i, ofGetHeight() - 50);
            continue;
        }

    }
}


void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case '1':
            if (!gpsActive) {
                gpsActive = true;
            }else {gpsActive = false;}
            break;
        case 'm':
            if (getHealth() < 3){
                health++;
            }
            break;
        case ' ':
        if (collectedPowerUps.size() > 0) {
            if (dynamic_cast<Cherry*>(collectedPowerUps[0])) {
                Cherry* cherry = dynamic_cast<Cherry*>(collectedPowerUps[0]);
                int xpos = cherry->getRandomTp()->getX();
                int ypos = cherry->getRandomTp()->getY();
                x = xpos;
                y = ypos;
                collectedPowerUps.erase(collectedPowerUps.begin());
                break;
            }
            if (dynamic_cast<Strawberry*>(collectedPowerUps[0])) {
                isInvencible = true;
                isInvis = true; 
                collectedPowerUps.erase(collectedPowerUps.begin());
                break;
            }
        }
            break;
            // SpeedBoost.activate(speed);
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }

void Player::swap(PowerUp* a, PowerUp* b){
    PowerUp* temp = a;
    a = b;
    b = temp;
}

void Player::checkCollisions(){


    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity : em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                EatCount += 1;
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
            }
            if(dynamic_cast<Strawberry*>(entity)) {
                Strawberry* powS = new Strawberry(entity->getX(),entity->getY(),16,16,spriteSheet);
                collectedPowerUps.push_back(dynamic_cast<PowerUp*>(powS));
                em->setMapCord(convertToCoordsY(entity->getY()),convertToCoordsX(entity->getX()),2);
                entity->remove = true;
            }
            if(dynamic_cast<Cherry*>(entity)) {
                Cherry* powC = new Cherry(entity->getX(),entity->getY(),16,16,spriteSheet);
                powC->setTpVec(dynamic_cast<Cherry*>(entity)->getTpSpots());
                collectedPowerUps.push_back(dynamic_cast<PowerUp*>(powC));
                em->setMapCord(convertToCoordsY(entity->getY()),convertToCoordsX(entity->getX()),2);
                entity->remove = true;
            }
            if (dynamic_cast<GreenFruit*>(entity)){
                entity->remove = true;
                score += ofRandom(500);
            }
            if (dynamic_cast<Orange*>(entity)){
                entity->remove = true;
                score += ofRandom(500);
            }
            if (dynamic_cast<Apple*>(entity)){
                entity->remove = true;
                score += ofRandom(500);
            }
            if (dynamic_cast<Bell*>(entity)){
                entity->remove = true;
                score += ofRandom(500);
            }
            if (dynamic_cast<Ship*>(entity)){
                entity->remove = true;
                int min_indx;
                for(unsigned int i=0; i < collectedPowerUps.size();i++){
                    min_indx = i;

                    for(unsigned int j =i; j < collectedPowerUps.size(); j++){
                        if(collectedPowerUps[j]->compareRank(collectedPowerUps[min_indx]) == false){
                            min_indx = j;
                        }
                    }
                    if(collectedPowerUps[min_indx]->compareRank(collectedPowerUps[i]) == false){
                        PowerUp* temp = collectedPowerUps[min_indx];
                        collectedPowerUps[min_indx] = collectedPowerUps[i];
                        collectedPowerUps[i] = temp;
                        continue;
                    }
                }
            }
        }

    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->setDead(true);
                ghost->remove = true;
                
            }
            else if (!isInvencible && !ghost->getDead()) {
                die();
            }
        }
    }
    for (unsigned int i = 0; i < GPSsquares.size(); i++) {
        if (GPSsquares[i].intersects(PacmanHitBox)) {
            GPSsquares.erase(GPSsquares.begin() + i);
        }
    }
}
void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}

void Player::UpdateCoords() {
     for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 40; j++) {
                this->setMapCord(j,i,em->getMapCoord(j,i));
            }
        }
        hasUpdated = true;
}

int Player::convertToCoordsX(int num) {
    int Offset = (ofGetWidth() - MapImage.getHeight()*16)/2;
    int out = (num - Offset) / pixelMultiplier; 
    return out;
}

int Player::convertToCoordsY(int num) {
    int Offset = (ofGetHeight() - MapImage.getWidth()*16)/2;
    int out = (num - Offset) / pixelMultiplier;
    return out;
}

string Player::GPSPath(int row, int col) {
    //----------------------------------------------------------------------
    if (row < 0 || row > 39)return "";
    if (col < 0 || col > 39)return "";
    if (em->getMapCoord(row,col) == 7) {
        return "[" + to_string(row) + "," + to_string(col) + "]";
        }
    if (em->getMapCoord(row,col) == 0)return "";
    if (em->getMapCoord(row,col) == 1)return "";
    em->setMapCord(row,col,1);
    path = GPSPath(row-1, col);
    if (!path.empty()) { 
        return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        }
    path = GPSPath(row+1, col);
    if (!path.empty()) { 
        return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        }  
    path = GPSPath(row, col+1);
    if (!path.empty()) { 
        return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        }  
    path = GPSPath(row, col-1);
    if (!path.empty()) {
        return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        } 
    return "";
}

void Player::GPS(string path) {
    int x;
    int y;
    vector<int> yVec;
    vector<int> xVec;
    for ( unsigned int i = 0; i < path.size(); i++) {
        if (path[i] == '[' || path[i] == ']') {continue;} 
        if (path[i] == ',') {continue;}     
        else if ((isdigit(path[i]) && isdigit(path[i+1])) && path[i+2] == ',') {
            y = convertToYPos(stoi(path.substr(i,2)));
            yVec.push_back(y);
            }
        else if ((isdigit(path[i]) && isdigit(path[i+1])) && path[i-1] == ',') {
            x = convertToXPos(stoi(path.substr(i,2)));
            xVec.push_back(x + 10);
            }
        else if ((isdigit(path[i]) && path[i+1] == ',') && !isdigit(path[i-1])) {
            y = convertToYPos(stoi(path.substr(i,1)));
            yVec.push_back(y);
            }
        else if (isdigit(path[i]) && path[i-1] == ',') {
            x = convertToXPos(stoi(path.substr(i,1)));
            xVec.push_back(x + 10);
            }
   }
   for (unsigned int i = 0; i < xVec.size(); i++) {
       ofRectangle rect(xVec[i],yVec[i],10,10);
       GPSsquares.push_back(rect);
   }
}


int Player::convertToXPos(int cord) {
    int Offset = (ofGetWidth() - MapImage.getHeight()*16)/2;
    return cord * pixelMultiplier + Offset;
}

int Player::convertToYPos(int cord) {
     int Offset = (ofGetHeight() - MapImage.getWidth()*16)/2;
     return cord * pixelMultiplier + Offset;
}

void Player::revertGPS() {
    for (int i = -1; i < 39; i++) {
        for (int j = -1; j < 39; j++) {
            if (em->getMapCoord(j,i) == 1) {
                em->setMapCord(j,i,2);
            }
        }
    }
    GPSsquares.clear();
    path = "";
}

