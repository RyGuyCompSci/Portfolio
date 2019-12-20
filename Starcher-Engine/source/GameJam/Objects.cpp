#include "Objects.h"
#include "Game.h"
#include "Scenes.h"
#include "GlobalVars.h"
#include <math.h>
#include <iostream>

#define PI 3.1415926535

int playerOneX=-1, 
    playerOneY=-1, 
    playerTwoX=-1, 
    playerTwoY=-1;

int current_scene = 0;

int num_lives = 3;

std::clock_t switch_timer = std::clock();
std::clock_t bullet_timer = std::clock();

/* Background */
Background::Background(unsigned int sprite_num, float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav) 
: Object(x, y, collisionLayer, collisionFlags, grav) 
{
    init(sprite_num);
}

void Background::init(unsigned int sprite_num) {
    setSprite(sprite_num);
}

/* Player */
Player::Player(int id, unsigned int sprite_num, float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav) 
: Object(x, y, collisionLayer, collisionFlags, grav) 
{
    if(playerOneX == -1 && id == 0) playerOneX = x;
    else this->x = playerOneY;
    if(playerTwoX == -1 && id == 1) playerTwoX = x;
    else this->y = playerOneY;
    if(playerOneY == -1 && id == 0) playerOneY = y;
    else this->x = playerTwoX;
    if(playerTwoY == -1 && id == 1) playerTwoY = y;
    else this->y = playerTwoY;

    this->debug = true;
    this->addHitBox(22,20,20,76);
    this->id = id;
    init(sprite_num);
}

void Player::init(unsigned int sprite_num) {
    setSprite(sprite_num);
}

void Player::onCollide(Object *other, int myBoxId, int otherBoxId) {
    std::cout << "Collided\n";
    if(other->collisionFlags & PROJECTILE) {
        num_lives--;
        destroyObject(other);
    }
}

void Player::process(double delta) {
    int player_movement_speed = 3;
    bool moving = false;
    if(Keys::isKeyPressed(Keys::W)) {
		this->y -= player_movement_speed;
        moving = true;
        this->setSprite((unsigned int) (facing_right ? 3 + (this->id * 3) : 4 + (this->id * 3) ));
	}
	if(Keys::isKeyPressed(Keys::A)) {
		this->x -= player_movement_speed;
        this->setSprite((unsigned int) 4 + (this->id * 3));
        moving = true;
        facing_right = false;
	}
	if(Keys::isKeyPressed(Keys::S)) {
		this->y += player_movement_speed;
        moving = true;
        this->setSprite((unsigned int) (facing_right ? 3 + (this->id * 3) : 4 + (this->id * 3) ));
	}
	if(Keys::isKeyPressed(Keys::D)) {
		this->x += player_movement_speed;
        this->setSprite((unsigned int) 3 + (this->id * 3));
        moving = true;
        facing_right = true;
	}
    if(Keys::isKeyPressed(Keys::E)) {
        if((std::clock() - switch_timer) / ((double) CLOCKS_PER_SEC / 24) > 2.5) {
            switch_timer = std::clock();
            if(id == 0) {
                playerOneX = this->x;
                playerOneY = this->y;
            } else {
                playerTwoX = this->x;
                playerTwoY = this->y;
            }
            jumpReality(this->id);
        }
    }

    if(!moving) {
        this->setSprite((unsigned int) 2 + (this->id * 3));
    }

    if(this->x < 0) this->x = 0;
    if(this->y < -20) this->y = -20;
    if(this->x + PLAYER_WIDTH > WINDOW_WIDTH) this->x = WINDOW_WIDTH - PLAYER_WIDTH;
    if(this->y + PLAYER_HEIGHT > WINDOW_HEIGHT) this->y = WINDOW_HEIGHT - PLAYER_HEIGHT;


}

void Player::jumpReality(int id) {
    if(!current_scene) { // earth
        current_scene++;
    } else { // parallel
        current_scene--;
    }
    setActiveScene((unsigned int) current_scene);
}



Enemy::Enemy(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav) 
: Object(x, y, collisionLayer, collisionFlags, grav) {
    init();
}

void Enemy::init() {
    this->setSprite((unsigned int) 8);
}

void Enemy::process(double delta) {
    if((std::clock() - bullet_timer) / ((double) CLOCKS_PER_SEC / 24) > 7) {
        bullet_timer = std::clock();
        attack();
    }
}

void Enemy::attack() {
    std::vector<Object *> sceneObjs = activeEngine->getActiveScene()->getObjectList();
    Player *p;
    for(auto o : sceneObjs) {
        if(dynamic_cast<Player *>(o)) {
            p = (Player *)o;
        } else if(dynamic_cast<Projectile *>(o) 
            && (o->x < 0 || o->x > WINDOW_WIDTH || o->y < 0 || o->y > WINDOW_HEIGHT)) {
            //let's also get rid of profectiles we aren't using :D
            destroyObject(o);
        }
    }
    int projectile_speed = 7;
    int offset_x = this->x + 32, 
        offset_y = this->y + 24;
        // p->x = p->x + PLAYER_WIDTH / 2,
        // p->y = p->y + PLAYER_HEIGHT / 2;
    double dist = sqrt(pow((p->x - offset_x), 2) + pow((p->y- offset_y), 2));
    if(dist < 400) {
        this->setSprite((unsigned int) 9);
        bullet_timer = std::clock();
        double vx = (p->x - this->x) * (projectile_speed / dist);
        double vy = (p->y - this->y) * (projectile_speed / dist);
        Projectile *pr = new Projectile(this->x + 32, this->y + 24, vx, vy);
        activeEngine->getActiveScene()->addObject(pr);
    } else {
        this->setSprite((unsigned int) 8);
    }
}

Projectile::Projectile(float x, float y, float vx, float vy, int collisionLayer, unsigned int collisionFlags, bool grav) 
: Object(x, y, collisionLayer, collisionFlags, grav) {
    this->vx = vx;
    this->vy = vy;
    this->setSprite((unsigned int) 10);
    this->addHitBox(8,8,16,16);
    this->debug = true;
}

void Projectile::process(double delta) {
    this->x += this-> vx;
    this->y += this-> vy;
}