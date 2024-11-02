#include "CharacterState.h"

CharacterState::CharacterState() {
    pacman = new Button(ofGetWidth()/2-125, ofGetHeight()/2, 64, 50, "Pacman");
    msPacman = new Button(ofGetWidth()/2-20, ofGetHeight()/2, 64, 50, "Ms. Pacman");
    pacmanImg.load("images/pacman.png");
    msPacmanImg.load("images/mspacman.png");
    vector<ofImage> pacmananim;
    vector<ofImage> msPacmananim;
    ofImage temp;
    ofImage temp2;
    for (int i = 0; i < 3; i++) {
        temp.cropFrom(pacmanImg, i*16, 0, 16, 16);
        pacmananim.push_back(temp);
    }
    for (int i = 0; i < 3; i++) {
        temp2.cropFrom(msPacmanImg, i*16, 0, 16, 16);
        msPacmananim.push_back(temp2);
    }
    pacAnim = new Animation(10, pacmananim);
    msPacAnim = new Animation(10, msPacmananim);
}   

void CharacterState::tick() {
    pacman->tick();
    msPacman->tick();
    pacAnim->tick();
    msPacAnim->tick();
    if (pacman->wasPressed()) {
        setNextState("Game");
        setFinished(true);
        isMsPacman = false;
    }
    if (msPacman->wasPressed()) {
        setNextState("Game");
        setFinished(true);
        isMsPacman = true;
    }
}

void CharacterState::render() {
    string title = "Select Your Character";
    ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
    ofSetBackgroundColor(0,0,0);
    ofSetColor(256,256,256);
    pacAnim->getCurrentFrame().draw(ofGetWidth()/2-125, ofGetHeight()/2-100, 100, 100);
    msPacAnim->getCurrentFrame().draw(ofGetWidth()/2-20, ofGetHeight()/2-100, 100, 100);
    pacman->render();
    msPacman->render();

}

void CharacterState::keyPressed(int key) {

}

void CharacterState::mousePressed(int x, int y, int button) {
    pacman->mousePressed(x, y);
    msPacman->mousePressed(x, y);
}

void CharacterState::reset() {
    setFinished(false);
    setNextState("");
    isMsPacman = false;
    pacman->reset();
    msPacman->reset();
}

CharacterState::~CharacterState() {
    delete pacman;
    delete msPacman;
    delete pacAnim;
    delete msPacAnim;
}