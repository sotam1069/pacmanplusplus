#pragma once 

#include "State.h"
#include "Button.h"
#include "Animation.h"

class CharacterState : public State {
    private:
        Button *pacman;
        Button *msPacman;
        bool isMsPacman = false;
        Animation *pacAnim;
        Animation *msPacAnim;
        ofImage pacmanImg;
        ofImage msPacmanImg;

    public:

        CharacterState();
        ~CharacterState();
        void setIsMsPacman(bool b) {isMsPacman = b;};
        bool getIsMsPAcman() {return isMsPacman;};
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset();


};