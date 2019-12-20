#include "objects.h"
#include <iostream>

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void player::init() {
    setSprite((unsigned int) 2);
    this->debug = false;
    this->addHitBox(6,42,33,22);
}

void player::is_standing() {
    setSprite((unsigned int) 1);
}

void player::onCollide(Object *other, int myBoxID, int otherBoxID) {
    if(other->collisionFlags == ENEMY && !this->is_dead) {
        this->is_dead = true;
        std::cout << "Dead" << std::endl;
        setSprite((unsigned int) 5);

    }
    if(this->x >= other->x + 5 && other->collisionFlags == GROUND) {
        this->gravity = false;
		this->y = 256 - (other->sprite->height + this->sprite->height); // put them on the ground
    }
}

void player::process(double delta) {
    std::cout << this->x << std::endl;
    if(!this->is_dead) {
        if(!this->gravity && Keys::isKeyPressed(Keys::W)) {
            this->yV = -26;
            this->gravity = true;
        }
        if(this->gravity) {
            if(yV < 0.0) {
                yV = 3 * (yV/4);
            }
        }
        if(this->sprite->getImageNum() != (unsigned int) 1) this->x += 8; //gotta go fast!
    }
    if (this->y <= 0) this->y = 0;
}


/**
 * Member functions for the hurdle class
 */
hurdle::hurdle(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void hurdle::init() {
    setSprite((unsigned int) 3);
    this->addHitBox(16,16,31,48);
}


/**
 * Member functions for the background class
 */
background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void background::init() {
    setSprite( (unsigned int) 0);
}


/**
 * Member functions for the ground class
 */
ground::ground(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void ground::init() {
    this->debug = false;
    setSprite((unsigned int) 4);
    this->addHitBox(0,0, this->sprite->width, this->sprite->height);
}


/**
 * Member functions for the scenetrigger class
 */
sceneTrigger::sceneTrigger(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    set_scene((unsigned int) 1);
}

void sceneTrigger::set_scene(unsigned int scene_num) {
    this->scene_num = scene_num;
}

void sceneTrigger::process(double delta) {
    if(Keys::isKeyPressed(Keys::Space)) {
        resetScene(levels[1],1);
        setActiveScene(1);
    }
}
