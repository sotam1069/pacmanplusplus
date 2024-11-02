#pragma once

#include "PowerUp.h"
#include "Whitepixel.h"


class Cherry : public PowerUp, public Entity {

    private:
        int rank = 1;
        string name = "Teleportation";
        bool isActive = false;
        vector<White*> TeleportationSpots;

    public:
        Cherry(int x, int y, int width, int height, ofImage spriteSheet);
        void activate(int &num);
        void setIsActive(bool b) {isActive = b;}
        bool getIsActive() {return isActive;}
        void setTpSpots(White* v){
            TeleportationSpots.push_back(v);
        }
        void setTpVec(vector<White*> v){
            TeleportationSpots = v;
        }
        White* getRandomTp(){
            return TeleportationSpots[ofRandom(TeleportationSpots.size())];
        }

        int getRank() {return rank;}
        string getName() {return name;}
        bool compareRank(PowerUp* p);
        vector<White*> getTpSpots() {return TeleportationSpots;}

};