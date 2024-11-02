#include "PauseState.h"

PauseState::PauseState() {
    quit = new Button(ofGetWidth()/2, ofGetHeight()/2 - 100, 64, 50, "Quit");
    resume = new Button(ofGetWidth()/2, ofGetHeight()/2 - 40, 64, 50, "Resume");
}

void PauseState::render() {
    string title = "Paused";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
    ofSetBackgroundColor(0,0,0);
    quit->render();
    resume->render();
}

void PauseState::keyPressed(int key) {

}

void PauseState::tick() {
    quit->tick();
    resume->tick();
    if (quit->wasPressed()) {
        setFinished(true);
        setNextState("Menu");
        isPaused = false;
    }
    if (resume->wasPressed()) {
        setFinished(false);
        setNextState("Game");
        Resumed = true;
    }

}

void PauseState::mousePressed(int x, int y, int button) {
    quit->mousePressed(x,y);
    resume->mousePressed(x,y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	quit->reset();
    resume->reset();
}

PauseState::~PauseState(){
	delete quit;
    delete resume;
}