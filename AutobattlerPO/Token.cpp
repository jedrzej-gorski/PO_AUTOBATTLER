#include "Token.h"
#include <fstream>
#include <iostream>

ANIMATION_MAP createAnimationList(std::string unitType) {
	std::ifstream fileStream(unitType + "/animations.txt");
	ANIMATION_MAP animationList;

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
}

int getEndFrameIndex(ANIMATION_MAP animationList, std::string unitType) {
	if (animationList.empty()) {
		std::cout << "ERROR - ANIMATION MAP EMPTY IN " << unitType;
		return 0;
	}
	else {
		return std::get<1>((--animationList.end())->second);
	}
}

Token::Token(std::string unitType, int x, int y, SPRITE_MAP &imageData) : animationFrameList(createAnimationList(unitType)), Sprite(TokenSprite(unitType, getEndFrameIndex(animationFrameList, unitType), imageData)) {
	xPos = x;
	yPos = y;
	xVel = 0;
	yVel = 0;
	currentTexture = sf::Texture();
	animationQueue = std::queue<animationTag>();
}

void Token::newAnimation(animationTag nextAnimation) {
	animationQueue.push(nextAnimation);
}

void Token::setNextTexture() {
	if (animationQueue.empty()) {
		std::cout << "ERROR - ANIMATION QUEUE EMPTY";
	}
	else {
		if (!Sprite.setNextFrame()) {
			animationQueue.pop();
			Sprite.setAnimationFrames(std::get<0>(animationFrameList[animationQueue.front()]), std::get<1>(animationFrameList[animationQueue.front()]));
		}
		currentTexture = Sprite.getCurrentAnimationFrame();
	}
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