#include "Map.h"

Map::Map(EntityManager* em){
    entityManager = em;
	for (int i = 0;i < 40; i++) { //sets all matrix spaces to 0;
		for (int j = 0; j < 40; j++) {
			mapMatrix[j][i] = 0;
			em->setMapCord(j,i,0);
		}
	}
}

void Map::tick(){
	entityManager->tick();
	player->tick();
	gs->tick();

}
void Map::render(){
    ofSetBackgroundColor(0, 0, 0);
	entityManager->render();
	player->render();

}

void Map::keyPressed(int key){
	player->keyPressed(key);
	gs->keyPressed(key);

}

void Map::mousePressed(int x, int y, int button){
	player->mousePressed(x, y, button);
}

void Map::keyReleased(int key){
	player->keyReleased(key);
}
void Map::addBoundBlock(BoundBlock* e){
    entityManager->boundBlocks.push_back(e);
}
void Map::addEntity(Entity* e){
	entityManager->entities.push_back(e);
}
void Map::addRandomSpot(White* w) {
	RandomSpots.push_back(w);
}
void Map::setPlayer(Player* p){
    player = p;
}
void Map::UpdateEmCoords() {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			entityManager->setMapCord(j,i,mapMatrix[j][i]);
		}
	}
}
Player* Map::getPlayer(){
	return player;
}

void Map::setGhostSpawner(GhostSpawner* p){
    gs = p;
}

vector<Entity*> Map::getEntities(){
	return entityManager->entities;
}

Map::~Map(){
	delete player;
	delete entityManager;
	delete gs;
	RandomSpots.clear();
}