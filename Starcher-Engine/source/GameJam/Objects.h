#ifndef OBJECTS_H
#define OBJECTS_H
#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include <vector>

class Player : public Object {
        std::vector<Object> inventory;
        bool right = true, facing_right = true;
        int id;
    public:
        Player(int id, unsigned int sprite_num, float x, float y, int collisionLayer = 0, unsigned int collisionFlags = PLAYER, bool grav = false);
        void init(unsigned int sprite_num);
        void onCollide(Object *other, int myBoxId, int otherBoxId);
        void process(double delta);
        void jumpReality(int id);

};

class Background : public Object {
    public:
        Background(unsigned int sprite_num, float x = 0, float y = 0, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void init(unsigned int sprite_num);
};

class Projectile : public Object {
    float vx, vy;
    public:
    Projectile(float x, float y, float vx, float vy, int collisionLayer = 0, unsigned int collisionFlags = PROJECTILE, bool grav = false);
    // void init();
    void process(double delta);
    bool operator==(const Projectile &other) {
        return this == &other;
    }
};

class Enemy : public Object {
    std::vector<Projectile> activeProjectiles;
    public:
        Enemy(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void init();
        void attack();
        void process(double delta);
};

#endif