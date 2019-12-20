
#ifndef OBJECTS_H
#define OBJECTS_H
#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include "globalvars.h"
#include <vector>

class player: public Object {
public:
    int set_index = 0;
	bool on_ground = true;
    bool is_dead = false;
    std::vector<unsigned int> spriteSet;
    player(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=true);
    void init();
    void onCollide(Object *other, int myBoxID, int otherBoxID);
    void process(double delta);
    void is_standing();
};

class hurdle: public Object {
public:
    hurdle(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

class background: public Object
{
public:
    background(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

class ground: public Object {
public:
    ground(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

class sceneTrigger: public Object {
public:
    unsigned int scene_num;
    sceneTrigger(float x=0, float y=0, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
    void set_scene(unsigned int scene_num);
    void process(double delta);
};

#endif
