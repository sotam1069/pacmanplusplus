#include "WinState.h"

WinState::WinState(){
    menu = new Button(ofGetWidth()/2-40, ofGetHeight()/2 - 100, 40, 50, "Quit");
}

void WinState::render(){
    string title = "You have Won!";
    ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
    ofSetBackgroundColor(0,0,0);
    menu->render();
}

void WinState::keyPressed(int key){

}

void WinState::tick(){
    menu->tick();
    if (menu->wasPressed()){
        setFinished(true);
        setNextState("Menu");
    }
}

void WinState::mousePressed(int x, int y, int button){
    menu->mousePressed(x,y);
}

void WinState::reset(){
    setFinished(false);
    setNextState("");
    menu->reset();
}

WinState::~WinState(){
    delete menu;
}