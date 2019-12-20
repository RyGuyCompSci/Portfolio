#include "headers/HitBox.hpp"


HitBox::HitBox(float offsetX, float offsetY, int width, int height, double ttl){
	this->type = 0;	
    	this->offsetX = offsetX;
	this->offsetY = offsetY;
	
	this->width = width;
	this->height = height;

	this->ttl = ttl;
	if(ttl < 0.0){
		this->infinite = true;
	}else{
		this->infinite = false;
	}

}

//Decrements the TTL on the hitbox
double HitBox::decTime(double delta){
	if(this->infinite == false){
		this->ttl -= delta;
	}
	return this->ttl;
}
