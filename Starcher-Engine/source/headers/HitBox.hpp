#ifndef HITBOX_H
#define HITBOX_H

class HitBox{
	public:
	    float offsetX;
	    float offsetY;
	    int width;
	    int height;
	    double ttl;
	    bool infinite;
	    int type;

	    HitBox(float offsetX, float offsetY, int width, int height, double ttl=-1);
	    double decTime(double delta); //(if ttl > 0 && ttl - delta <= 0){ttl = ttl - 1;} return ttl

};
#endif
