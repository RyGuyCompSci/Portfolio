#ifndef SPRITE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#define SPRITE_H



class Sprite {
	private:
			std::vector<std::string> imagePaths; //Store file paths to each image. We need a way to store images in memory for easy access
			std::vector<sf::Texture> images; //sf::Images are created after image is loaded from a file
	public:
			int xOffset;
			int yOffset;
			int width;
			int height;
			bool repeated;
			
			Sprite(std::string path);
			/*
				Returns 0 on success -1 on failure. Should declare a new image, load it from a file and place that image in our 
				images vector
			*/
			bool addImage(std::string filePath);
			/*
				Remove an image from the Sprite based on its' location in the images array
			*/
			int removeImage(int index); 

			sf::Texture getImage(int index);

			std::string getImagePath(int index);
			void setRepeated(bool repeat);
			void setSize(int width, int height);
			unsigned int getImageNum();

};
#endif
