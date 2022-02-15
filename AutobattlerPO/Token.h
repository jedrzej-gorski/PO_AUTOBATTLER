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
		int width;
		int height;
		TokenSprite Sprite;
		sf::Texture currentTexture;
		std::queue<animationTag> animationQueue;
		ANIMATION_MAP animationFrameList;
	public:
		Token(std::string unitType, int x, int y, SPRITE_MAP &imageData, int size);
		void newAnimation(animationTag nextAnimation);
		sf::Texture* getNextTexture();
		void setPosition(int x, int y);
		void setVelocity(int x, int y);
		void setWidth(int x);
		void setHeight(int y);
		std::tuple<int, int> getPosition();
		int getWidth();
		int getHeight();
		void moveToken();

}; 
#endif

