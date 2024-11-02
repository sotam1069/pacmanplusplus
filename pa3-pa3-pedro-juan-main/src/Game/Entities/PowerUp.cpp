
#include "PowerUp.h"

int PowerUp::getRank(){
    
    return rank;
}

bool PowerUp::compareRank(PowerUp* p){

    if(this->getRank() > p->getRank()){
        return true;
    }
    else{ return false;}

}

string PowerUp::getName(){

    return name;
}