#include "MapBuilder.h"


MapBuilder::MapBuilder(){
	entityManager = new EntityManager();
	pixelMultiplier = 16;
	boundBoundBlock = ofColor(0,0,0);
	pacman = ofColor(255,255, 0);
	ghostC = ofColor(25, 255,0);
	dotC = ofColor(255, 10, 0);
	bigDotC = ofColor(167, 0, 150);
	CherryC = ofColor(63,81,181);
	StrawberryC = ofColor(255,106,230);
	GreenFruitC = ofColor(0,255,0);
	OrangeC = ofColor(255,183,81);
	AppleC = ofColor(255,0,0);
	ShipC = ofColor(0,255,230);
	BellC = ofColor(222,222,255);
	whiteC = ofColor(255,255,255);

	pacmanSpriteSheet.load("images/Background.png");
	tempBound.cropFrom(pacmanSpriteSheet, 603,18,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 615,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 635,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,57,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,75,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 656,116,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 656,136,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,174,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,155,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,192,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 664,232,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,191,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 494,191,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,208,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,223,16,16);
	bound.push_back(tempBound);//single
}

Map* MapBuilder::createMap(ofImage mapImage , bool IsMsPacman){
	int xOffset = (ofGetWidth() - mapImage.getWidth()*pixelMultiplier)/2;
	int yOffset = (ofGetHeight() - mapImage.getHeight()*pixelMultiplier)/2;
	bool b = IsMsPacman;
	int RandomFruitCount = 0;
	ofPixels pixels = mapImage.getPixels();
	Map* mapInCreation =  new Map(entityManager);
    for (volatile int i = 0; i < mapImage.getWidth(); i++) {
        for (volatile int j = 0; j < mapImage.getHeight(); j++) {
            ofColor currentPixel = pixels.getColor(i, j);
            int xPos = i*pixelMultiplier + xOffset;
            int yPos = j*pixelMultiplier + yOffset;
            if(currentPixel == boundBoundBlock){
                BoundBlock* BoundBoundBlock = new BoundBlock(xPos,yPos,pixelMultiplier,pixelMultiplier,getSprite(mapImage,i,j));
                mapInCreation->addBoundBlock(BoundBoundBlock);
				mapInCreation->setMapCoord(j,i,0); //bounds = 0
				entityManager->setMapCord(j,i,0);
			}if (currentPixel == whiteC){
				White* whiteC = new White(xPos, yPos, pixelMultiplier, pixelMultiplier, pacmanSpriteSheet);
				mapInCreation->addRandomSpot(whiteC);
				mapInCreation->setMapCoord(j,i,2);  //viable path = 2
				entityManager->setMapCord(j,i,2);
			}else if(currentPixel == pacman){
                Player* PacMan = new Player(xPos,yPos,pixelMultiplier,pixelMultiplier, entityManager, b);
				mapInCreation->setPlayer(PacMan);
				mapInCreation->setMapCoord(j,i,2);
				entityManager->setMapCord(j,i,2);
            }else if(currentPixel == ghostC){
                GhostSpawner* ghostSpawn = new GhostSpawner(xPos,yPos,pixelMultiplier,pixelMultiplier,entityManager, pacmanSpriteSheet);
                mapInCreation->setGhostSpawner(ghostSpawn);
				mapInCreation->setMapCoord(j,i,5); //ghost spawn = 5
				entityManager->setMapCord(j,i,5);
            }else if(currentPixel == dotC){
                Dot* dot = new Dot(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                mapInCreation->addEntity(dot);
				mapInCreation->setMapCoord(j,i,2);
				entityManager->setMapCord(j,i,2);
            }else if(currentPixel == bigDotC){
                BigDot* bigDot = new BigDot(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                mapInCreation->addEntity(bigDot);
				mapInCreation->setMapCoord(j,i,2);
				entityManager->setMapCord(j,i,2);
            }
			else if(currentPixel == StrawberryC){
				Strawberry* strawb = new Strawberry(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
				mapInCreation->addEntity(strawb);
				mapInCreation->setMapCoord(j,i,7); //special PU's = 7
				entityManager->setMapCord(j,i,7);
			}
			else if(currentPixel == CherryC){
				Cherry* cherryc = new Cherry(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
				mapInCreation->addEntity(cherryc);
				mapInCreation->setMapCoord(j,i,7);
				entityManager->setMapCord(j,i,7);
			}
        }
    }
	while (RandomFruitCount <= 7) {
		vector<string> fruits = {"apple", "Green Fruit", "Ship", "Orange", "Bell"};
		White* w = mapInCreation->getRandomSpot();
		int x = w->getX();
		int y = w->getY();
		string RandomFruit = fruits[static_cast<int>(ofRandom(fruits.size()))];
		if (RandomFruit == "apple") {
			Apple* applec = new Apple(x,y, pixelMultiplier, pixelMultiplier, pacmanSpriteSheet);
			mapInCreation->addEntity(applec);
		}else if (RandomFruit == "Green Fruit") {
			GreenFruit* greenC = new GreenFruit(x,y, pixelMultiplier, pixelMultiplier, pacmanSpriteSheet);
			mapInCreation->addEntity(greenC);
		}else if (RandomFruit == "Orange") {
			Orange* orangeC = new Orange(x,y, pixelMultiplier, pixelMultiplier, pacmanSpriteSheet);
			mapInCreation->addEntity(orangeC);
		}else if (RandomFruit == "Bell") {
			Bell* bellC = new Bell(x,y, pixelMultiplier, pixelMultiplier, pacmanSpriteSheet);
			mapInCreation->addEntity(bellC);
		}
		RandomFruitCount++;						
	}
	RandomFruitCount = 0;

	for(Entity* ent : mapInCreation->getEntities()) {
		if (dynamic_cast<Cherry*>(ent) != nullptr){
			dynamic_cast<Cherry*>(ent)->setTpSpots(mapInCreation->getRandomSpot());
		}
	}
    return mapInCreation;

}

int MapBuilder::getDotCount(ofImage mapImage) {
	int DotCount = 0;
	//
	ofPixels pixels = mapImage.getPixels();
	for (int i = 0; i < mapImage.getWidth(); i++) {
        for (int j = 0; j < mapImage.getHeight(); j++) {
            ofColor currentPixel = pixels.getColor(i, j);
            if(currentPixel == dotC || currentPixel == bigDotC){
               DotCount += 1;
        	}
		}
	}
	return DotCount;
}


ofImage MapBuilder::getSprite(ofImage mapImage, int i, int j){
	ofColor currentPixel = boundBoundBlock;
	ofPixels pixels = mapImage.getPixels();
	ofColor leftPixel;
	ofColor rightPixel;
	ofColor upPixel;
	ofColor downPixel;
	if (i>0) {
		leftPixel = pixels.getColor(i - 1, j);
	}else{
		leftPixel = pacman;

	}
	if (i<mapImage.getWidth()-1) {
		rightPixel = pixels.getColor(i + 1, j);
	}else{
		rightPixel= pacman;

	}
	if (j>0) {
		upPixel = pixels.getColor(i, j - 1);
	}else{
		upPixel = pacman;

	}
	if (j<mapImage.getHeight()-1) {
		downPixel = pixels.getColor(i, j + 1);
	}else{
		downPixel = pacman;

	}

	if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[1];
	}else if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[2];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[3];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[4];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[5];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[6];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[7];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[8];
	}else if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[9];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[10];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[11];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[12];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[13];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[14];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[15];
	}else{

		return  bound[0];
	}
}