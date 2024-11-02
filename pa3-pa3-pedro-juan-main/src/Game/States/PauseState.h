#pragma once

#include "State.h"
#include "Button.h"

class PauseState : public State {
    private:
        Button *quit;
        Button *resume;
        bool isPaused = false;
        bool Resumed = false;
    public:
        PauseState();
        ~PauseState();
        void render();
        void tick();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset(); 
        bool getIsPaused() {return isPaused;}
        void setIsPaused(bool b) {isPaused = b;}
        void setResumed(bool b) {Resumed = b;}
        bool getResumed() {return Resumed;}

};