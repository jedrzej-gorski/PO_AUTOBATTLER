#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Unit.h"
#include "Token.h"
#include "Common.h"
#include "UnitController.h"

class Scene {
	protected:
		sf::Texture sceneBackground;
		UNIT_MAP unitData;
		SPRITE_MAP imageData;
		sf::RenderWindow* gameWindow;
	public:
		Scene();
		virtual void startScene() {};
		virtual void setBackground() {};
		void drawBackground();
		virtual bool processKeyboard(sf::Keyboard::Key keyToCheck) {};
		virtual void drawSprites() {};
		virtual void processMouseInput(sf::Vector2i relativeMousePosition) {};
		virtual std::tuple<std::vector<Unit>, std::vector<std::string>> getTransitionData() {};
};

#endif
