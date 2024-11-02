#pragma once

#include <string>

using namespace std;

class PowerUp{

    private:
        int rank;
        string name;

    public: 
        virtual void activate(int &num) = 0;
        virtual bool getIsActive() = 0;
        virtual void setIsActive(bool b) = 0;
        int getRank();
        virtual bool compareRank(PowerUp* p);
        virtual string getName();
};