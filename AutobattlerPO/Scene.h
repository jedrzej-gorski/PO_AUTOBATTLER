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
	public:
		Scene();
		void terminateScene();
		void stepScene();
		void setBackground();
		void drawBackground();
		void drawSprites();
		virtual void processMouseInput(sf::Vector2i relativeMousePosition, int mouseButton) {};
		virtual std::tuple<std::vector<Unit>, std::vector<std::string>> getTransitionData() {};
};

#endif
