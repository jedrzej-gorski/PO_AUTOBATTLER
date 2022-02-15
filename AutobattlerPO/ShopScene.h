#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "Scene.h"
#include "Unit.h"
#include "ShopController.h"

#include <vector>

class ShopScene : public Scene {
	private:
		ShopController controller;
		std::vector<Unit> drawnUnits;
		sf::Texture background;
	public:
		ShopScene(int savedLevel, std::vector<Unit*> savedTeam, UNIT_MAP passedUnitData, SPRITE_MAP passedImageData);
		void startScene();
		void resolveEventQueue();
		void setBackground();
		void processMouseInput(sf::Vector2i relativeMousePosition);
		bool processKeyboard(sf::Keyboard::Key keyToCheck);
		std::tuple<std::vector<Unit*>, std::vector<std::string>> getTransitionData();
		void drawSprites(sf::RenderWindow &gameWindow);

};

#endif