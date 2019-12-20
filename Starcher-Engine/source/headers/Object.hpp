#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include "HitBox.hpp"
#include "Sprite.hpp"
#include <SFML/Graphics.hpp>

#define Keys sf::Keyboard

struct drawData {
	//For the Object itself
	int x;
	int y;
	unsigned int imageIndex;
	Sprite *sprite;
	bool drawHitBoxes;
	int width;
	int height;
	bool repeated;
	//Scaling
	float xScale;
	float yScale;

	//For text :)
	bool hasText;
	int textX;
	int textY;
	bool relativeToObject;
	unsigned int fontSize;
	sf::Font textFont;
	sf::String textString;
	sf::Color textColor;

	uint8_t alpha;

};

//Developer can add to collisionFlags if they need additional functionality
enum collisionFlags {
    PLAYER = 0x1,
    ENEMY = 0x2,
    GROUND = 0x4,
    WALL = 0x8,
    PROJECTILE = 0x10,
    POWERUP = 0x20,
    DANGER_ALL = 0x40,
    GOAL = 0x80,
    PICKUP = 0x100
};

class Object{
	protected:

			int createHitBox(int offsetX,int offsetY,int width,int height,float ttl);

			/*
				Call HitBox.decTime and destroy hit box if ttl=0
			*/
			void decHitBoxes(double delta); 
			void addHitBox(int offsetX, int offsetY, int width, int height, double ttl=-1);
            void _processPhysics(float grav, float termVel);
	public:
			//Drawing text information
			bool hasText;
			void deleteHitBox(int id);
			int textX;
			int textY;
			unsigned int fontSize;
			bool relativeToObject;
			sf::Font textFont;
			sf::String textString;
			sf::Color textColor;
			void setText(int textX, int textY, unsigned int fontSize, bool relative, std::string fontFile, std::string textString);
			void setFontSize(unsigned int fontSize);
			void setTextColor(sf::Color textColor=sf::Color::White);
			void hideText();
			//Scale
			float xScale;
			float yScale;
			void setScale(float xScale, float yScale);
			//Transparency
			uint8_t alpha;
			//width/height
			int sprite_width;
			int sprite_height;

            //Position
			float x;
			float y;
			float xPrev;
			float yPrev;
            //Velocity
            float xV;
            float yV;
            //Acceleration
            float xA;
            float yA;
			//Friction: Decimal between 0 and 1
			float friction;

            //If the object should be affected by gravity
            bool gravity;

            unsigned int collisionFlags;

			/*
				When collisionLayer is 0, collide with everything. When collisionLayer is negative, doesn't collide with anything. Nonzero positive collisionLayer only collide with that layer
				Negative takes priority over zero. Meaning that should an object with cL = 0 collide with one with cL = -1, no collision processing should occur.
			*/
			int collisionLayer;
			
			/*
				Defined here instead of in Sprite object b/c same Sprite may be used for multiple object instances and will be at different points in animation
			*/
			unsigned int imageIndex; 
			//Keeps track of what sprite we have when using setSprite by index
			unsigned int sprite_index;
			bool dynamic;
			
			int renderLayer;

			/*
				Typically will be the same as in the Sprite instance, but it may be desired to be different for different objects so it is specified here as well.
			*/
			float animationDelay; //Measured in milliseconds per image
			float animationTime;
			Sprite *sprite;
			std::vector<HitBox *> hitBoxes;


			Object(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
			~Object();
			
			/*
				Call decHitBoxes() if X milliseconds have passed since last call.
			*/
			void _process(double delta, float gravity, float termVel); 
			void _animate(double delta);
			void _destroy();

			//Debug toggle to do things like draw hitboxes
			bool debug;

			/*
				Calculate what imageIndex should be displayed, package all necessary rendering information into a drawData struct
			*/
			struct drawData _draw();

			virtual void process(double delta);
			virtual void onCollide(Object *other,int myBoxID, int otherBoxID);
			virtual void create();
			void setSprite(Sprite *sprite);
			void setSprite(unsigned int index);
            Sprite* getSprite(unsigned int index);
			
			std::vector<HitBox *> getHitBoxes();
};
#endif
