#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofSetWindowTitle("C++ Game Box");
	//States
	menuState = new MenuState();
	gameState = new GameState();
	gameOverState = new GameOverState();
	pausedState = new PauseState();
	winState = new WinState();
	characterState = new CharacterState();
	// Initial State
	currentState = menuState;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	if (currentState != nullptr){
		currentState->tick();
		if(currentState->getNextState() == "pause") {
			pausedState->setIsPaused(true);
			currentState = pausedState;
		}
		if (pausedState->getNextState() == "Game") {
				currentState = gameState;
				pausedState->reset();
				gameState->setNextState("");
			}

		if (characterState->getIsMsPAcman()) {
			gameState->setIsMsPacman(true);
			characterState->setIsMsPacman(false);
			gameState->reset();
		}

		if(currentState->hasFinished()){
			if(currentState->getNextState() == "Menu"){
				currentState = menuState;
				winState->reset();
				pausedState->reset();
				gameState->setIsMsPacman(false);
			}else if(currentState->getNextState() == "Game"){
				currentState = gameState;
			}else if(currentState->getNextState() == "over"){
				gameOverState->setScore(gameState->getFinalScore());
				currentState = gameOverState;
			}else if (currentState->getNextState() == "Win"){
				currentState = winState;
			}else if (currentState->getNextState() == "Char"){

				currentState = characterState;
			}
			currentState->reset();
		}
	}
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (currentState != nullptr)
		currentState->render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr)
		currentState->keyPressed(key);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}
