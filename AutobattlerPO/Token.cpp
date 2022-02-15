#include "Token.h"
#include <fstream>
#include <iostream>

//the following is used for implementing animations
/*ANIMATION_MAP createAnimationList(std::string unitType) {
	std::ifstream fileStream(unitType + "/animations.txt");
	ANIMATION_MAP animationList;
	if (unitType == "NULL") {
		return animationList;
	}

	if (fileStream) {
		while (!fileStream.eof()) {
			animationTag animationName;
			int firstFrame, lastFrame;
			std::tuple<int, int> frameRange;

			fileStream >> animationName >> firstFrame >> lastFrame;
			frameRange = std::make_tuple(firstFrame, lastFrame);
			animationList.insert(std::pair<animationTag, std::tuple<int, int>>(animationName, frameRange));
		}
	}
	else {
		std::cout << "ERROR - FILE OPENING FAILED! - " + unitType + "/animations.txt" + "- " + unitType;
	}

	return animationList;
}*/

int getEndFrameIndex(ANIMATION_MAP animationList, std::string unitType) {
	if (unitType == "NULL") {
		return 0;
	}
	if (animationList.empty()) {
		std::cout << "ERROR - ANIMATION MAP EMPTY IN " << unitType;
		return 0;
	}
	else {
		return std::get<1>((--animationList.end())->second);
	}
}

Token::Token(std::string unitType, int x, int y, SPRITE_MAP &imageData, int size) : Sprite(TokenSprite(unitType, 0, imageData)) {
	xPos = x;
	yPos = y;
	width = size;
	height = size;
	xVel = 0;
	yVel = 0;
	currentTexture = sf::Texture();
	animationQueue = std::queue<animationTag>();
}

void Token::newAnimation(animationTag nextAnimation) {
	animationQueue.push(nextAnimation);
}

sf::Texture* Token::getNextTexture() {
	return Sprite.getCurrentTexture();
	//the following implementation would be used for animations
	/*if (animationQueue.empty()) {
		std::cout << "ERROR - ANIMATION QUEUE EMPTY";
	}
	else {
		if (!Sprite.setNextFrame()) {
			animationQueue.pop();
			Sprite.setAnimationFrames(std::get<0>(animationFrameList[animationQueue.front()]), std::get<1>(animationFrameList[animationQueue.front()]));
		}
		currentTexture = Sprite.getCurrentAnimationFrame();
	}*/
}

void Token::setPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

void Token::setVelocity(int x, int y) {
	xVel = x;
	yVel = y;
}

void Token::moveToken() {
	xPos += xVel;
	yPos += yVel;
}

void Token::setWidth(int x) {
	width = x;
}

void Token::setHeight(int y) {
	height = y;
}

std::tuple<int, int> Token::getPosition() {
	return std::make_tuple(xPos, yPos);
}

int Token::getWidth() {
	return width;
}

int Token::getHeight() {
	return height;
}