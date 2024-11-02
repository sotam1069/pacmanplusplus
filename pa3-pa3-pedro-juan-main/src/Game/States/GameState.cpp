#include "GameState.h"
#include "Entity.h"
#include "Ghost.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage , isMsPacman);
	Dots = MapBuilder().getDotCount(mapImage);
	spriteSheet.load("images/Background.png");
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	if (map->getPlayer()->getEatCount() == Dots) {
		setFinished(true);
		setNextState("Win");
		map->getPlayer()->setEatCount(0);
	}

	
	while(map->getPlayer()->getScore() >= 1000 && counter <= 0){
		White* w = map->getRandomSpot();
		int x = w->getX();
		int y = w->getY();
		Ship* ship = new Ship(x,y,16,16,spriteSheet);
		map->addEntity(ship);
		counter += 1;
		break;
	}

	for(Entity* entity : map->getEntityManager()->ghosts){
		Ghost* gh = dynamic_cast<Ghost*>(entity);
		if(gh->getDead() == true){
			int x = gh->getX();
			int y = gh->getY();
			Eyes* eye = new Eyes(x, y,10,5,gh->getEM(),spriteSheet,gh->getGS());
			for (int i = 0; i<40; i++) {
				for (int j = 0; j < 40; j++) {
					eye->setMapCord(j,i,gh->getMapCoord(j,i));
				}
			}
			eye->setPositions(gh->getPositions());
			map->addEntity(eye);
		}
	}


}
void GameState::render() {

	map->render();
}

void GameState::keyPressed(int key){

	if (key == 'p') {
		setNextState("pause");
	}
	if (key == 'y'){
		setNextState("Win");
		setFinished(true);
	}
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
	map = MapBuilder().createMap(mapImage , isMsPacman);
	counter = 0;
}

int GameState::getFinalScore(){
	return finalScore;
}

GameState::~GameState(){
	delete map;
}