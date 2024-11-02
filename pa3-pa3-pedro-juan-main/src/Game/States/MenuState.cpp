#include "MenuState.h"

MenuState::MenuState() {
	startButton = new Button(ofGetWidth()/2-32, ofGetHeight()/2, 64, 50, "Start");
	characterSelection = new Button(ofGetWidth()/2-32, ofGetHeight()/2 + 40, 64, 50, "Select your Character");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void MenuState::tick() {
	startButton->tick();
	anim->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);
	}
	if(characterSelection->wasPressed()) {
		setNextState("Char");
		setFinished(true);
	}
}
void MenuState::render() {
	string title = "Pacman Project";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	startButton->render();
	characterSelection->render();


}

void MenuState::keyPressed(int key){
	
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
	characterSelection->mousePressed(x, y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
	characterSelection->reset();
}

MenuState::~MenuState(){
	delete characterSelection;
	delete startButton;
	delete anim;
}