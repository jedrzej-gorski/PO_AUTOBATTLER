#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Token.h"
#include "Common.h"
#include "UnitController.h"

class Scene {
	private:
		sf::Texture sceneBackground;
		std::vector<Token> tokenList;
		std::queue<gameEvent> eventQueue;
	public:
		Scene();
		void terminateScene();
		void stepScene();
		void setBackground();
		void drawBackground();
		void drawSprites();
		virtual void resolveEventQueue() = 0;
};

#endif
