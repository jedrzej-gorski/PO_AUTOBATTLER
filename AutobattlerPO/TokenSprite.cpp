#include "TokenSprite.h"
#include <map>
#include <iostream>

TokenSprite::TokenSprite(std::string unitType, int lastFrame, SPRITE_MAP &imageData) {
	startFrame = 0;
	currentFrame = 0;
	endFrame = 0;

	if (unitType != "NULL") {
		if (imageData[unitType].size() == 0) {
			for (int i = 0; i <= lastFrame; i++) {
				sf::Texture newTexture;
				std::string texturePath = "../graphics/" + unitType + ".png";
				if (!currentTexture.loadFromFile(texturePath)) {
					std::cout << "ERROR - LOADING SPRITE " << i << " FOR " << unitType;
				}
				/*if (!newTexture.loadFromFile(texturePath)) {
					std::cout << "ERROR - LOADING SPRITE " << i << " FOR " << unitType;
				}
				imageData[unitType].push_back(newTexture);*/
			}
		}
		//frameList = &imageData[unitType];
	}
}

void TokenSprite::setAnimationFrames(int start, int end) {
	startFrame = start;
	endFrame = end;
	currentFrame = startFrame;
}

sf::Texture* TokenSprite::getCurrentTexture() {
	return &currentTexture;
}

sf::Texture* TokenSprite::getCurrentAnimationFrame() {
	//get address of element pointed by currentFrame in vector pointed by frameList
	return &((*frameList)[currentFrame]);
}

bool TokenSprite::setNextFrame() {
	if (currentFrame != endFrame) {
		currentFrame += 1;
		return true;
	}
	else {
		return false;
	}
}
