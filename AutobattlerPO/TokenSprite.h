#ifndef TOKENSPRITE_H
#define TOKENSPRITE_H

#include "Common.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class TokenSprite {
	private:
		std::vector<sf::Texture>* frameList;
		int currentFrame;
		int startFrame;
		int endFrame;
		sf::Texture currentTexture;
	public:
		TokenSprite(std::string unitType, int lastFrame, SPRITE_MAP& imageData);
		void setAnimationFrames(int, int);
		sf::Texture* getCurrentTexture();
		sf::Texture* getCurrentAnimationFrame();
		bool setNextFrame();
};
#endif