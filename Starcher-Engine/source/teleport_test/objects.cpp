#include "objects.h"
#include <iostream>

int player_x = 0, player_y = 0;
unsigned int current_scene = 0;
std::clock_t initial_switch = std::clock();

/* Player Constructor */
Player::Player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav) 
	: Object(x,y,collisionLayer,collisionFlags,grav) 
{
	if(!player_x) player_x = this->x;
	else this->x = player_x;
	if(!player_y) player_y = this->y;
	else this->y = player_y;
	init();
}

/* Initializer */
void Player::init() {
	setSprite((unsigned int) 2);
	//this->debug = false;
}


/* Processor */
void Player::process(double delta) {
	//std::cout << "X:" << this->x << " Y:" << this->y << std::endl;
	if(Keys::isKeyPressed(Keys::W)) {
		this->y -= 8;
	}
	if(Keys::isKeyPressed(Keys::A)) {
		this->x -= 8;
	}
	if(Keys::isKeyPressed(Keys::S)) {
		this->y += 8;
	}
	if(Keys::isKeyPressed(Keys::D)) {
		this->x += 8;
	}
	if(Keys::isKeyPressed(Keys::X)) {
		std::cout << ((std::clock() - initial_switch) / ((double CLOCKS_PER_SEC / 24))) << std::endl;
		if((std::clock() - initial_switch) / ((double) CLOCKS_PER_SEC / 24) > 1) {
		initial_switch = std::clock();
		player_x = this->x;
		player_y = this->y;
	//	std::cout << "Changed global x|y to: " << player_x << "|" << player_y << std::endl;
	//	std::cout << "Pressed the action key" << std::endl;
		change_reality();
		}
	}
}

/* Change dimension */
void Player::change_reality() {
	if(!current_scene) current_scene = 1;
	else current_scene = 0;
	std::cout << "setting to scene: " << current_scene << std::endl;
	resetScene(levels[current_scene], current_scene);
	setActiveScene((unsigned int) current_scene);
}

Background::Background(unsigned int sprite_num, float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav) 
	: Object(x,y,collisionLayer,collisionFlags,grav) 
{
	init(sprite_num);
}

void Background::init(unsigned int sprite_num) {
	this->debug = false;
	setSprite(sprite_num);
}

