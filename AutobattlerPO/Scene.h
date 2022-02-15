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
		UNIT_MAP unitData;
		SPRITE_MAP imageData;
	public:
		Scene(UNIT_MAP passedUnitData, SPRITE_MAP passedImageData);
		Scene() = default;
		virtual ~Scene() {};
		virtual void startScene() {};
		virtual void setBackground() {};
		virtual bool processKeyboard(sf::Keyboard::Key keyToCheck);
		virtual void drawSprites(sf::RenderWindow &gameWindow) {};
		virtual void processMouseInput(sf::Vector2i relativeMousePosition) {};
		virtual std::tuple<std::vector<Unit*>, std::vector<std::string>> getTransitionData();
};

#endif
