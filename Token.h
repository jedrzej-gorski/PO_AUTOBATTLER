#ifndef TOKEN_H
#define TOKEN_H

#include "TokenSprite.h"
#include "Common.h"
#include <string>
#include <tuple>
#include <queue>

class Token {
	private:
		int xPos;
		int xVel;
		int yPos;
		int yVel;
		TokenSprite Sprite;
		sf::Texture currentTexture;
		std::queue<animationTag> animationQueue;
		ANIMATION_MAP animationFrameList;
	public:
		Token(std::string unitType, int x, int y, SPRITE_MAP &imageData);
		void newAnimation(animationTag nextAnimation);
		void setNextTexture();
		void setPosition(int x, int y);
		void setVelocity(int x, int y);
		void moveToken();

}; 
#endif

