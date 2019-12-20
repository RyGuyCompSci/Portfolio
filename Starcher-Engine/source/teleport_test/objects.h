#ifndef OBJECTS_H
#define OBJECTS_H

#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include "globalvars.h"
#include <vector>

class Player : public Object {
	void change_reality();

	public:
		Player(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
		void init();
		//void onCollide(Object *other, int myBoxId, int otherBoxId);
		void process(double delta);
};

class Background : public Object {
	public:
		Background(unsigned int sprite_num, float x=0, float y=0, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
		void init(unsigned int sprite_num);

};

class SceneTrigger : public Object {
	public:
		SceneTrigger(float x=0, float y=0, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
		void setScene(unsigned int scene_num, float x, float y);
		void process(double delta);
};

#endif
