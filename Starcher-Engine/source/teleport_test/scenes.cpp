#include "scenes.h"
#include "objects.h"
#include "globalvars.h"
#include "../headers/Globals.hpp"
#include <string>
#include <vector>
#include <iostream>

Scene *earth_one() {
	Scene *earth = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);

	Background *bg = new Background(0);
	Player *p = new Player(64, 64, 1, 0, false);

	earth->addObject(bg);
	earth->addObject(p);

	return earth;
}

Scene *earth_two() {
	Scene *upsideDown = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);	

	Background *bg = new Background(1);
	Player *p = new Player(64, 64, 1, 0, false);

	upsideDown->addObject(bg);
	upsideDown->addObject(p);

	return upsideDown;
}
