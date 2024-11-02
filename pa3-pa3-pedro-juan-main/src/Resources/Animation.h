#pragma once

#include "ofMain.h"

class Animation {

private:
	int speed, index;
	int timer;
	std::vector<ofImage> frames;
	bool end = false;
public:
	Animation(int speed, std::vector<ofImage> frames);
	void tick();
	ofImage getCurrentFrame();
	void reset();

};