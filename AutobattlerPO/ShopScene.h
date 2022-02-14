#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "Scene.h"
#include "Unit.h"
#include "ShopController.h"

#include <vector>

class ShopScene : public Scene {
	private:
		ShopController controller;
	public:
		ShopScene(int savedLevel, std::vector<Unit> savedTeam, UNIT_MAP passedUnitData, SPRITE_MAP passedImageData) : controller(ShopController(savedLevel, savedTeam)) {};
		void startScene();
		void resolveEventQueue();
		void processMouseInput(sf::Vector2i relativeMousePosition, int mouseButton);
		std::tuple<std::vector<Unit>, std::vector<std::string>> getTransitionData();
};

#endif