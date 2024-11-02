#pragma once

#include "State.h"
#include "Button.h"

class WinState : public State {

    private: 
        Button *menu;
        bool wstate = false;

    public:
        WinState();
        ~WinState();
        void render();
        void tick();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset(); 
        bool getWinState() {return wstate;}
        void setWinState(bool w) {wstate = w;}
};