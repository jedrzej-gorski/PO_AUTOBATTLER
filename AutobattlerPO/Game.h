#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "Scene.h"
#include <map>

class Game {
	private:
		int turn;
		int savedRank;
		int currentPhase;
		Scene *currentScene;
		//Scene currentScene
		SPRITE_MAP graphicData;
		UNIT_MAP unitData;
		sf::RenderWindow* gameWindow;
	public:
		Game(sf::RenderWindow* passedWindow);
		void changeScene();
		void initializeGame();
		void passMouseInput(sf::Vector2i relativeMousePosition);
		void drawScene();
		void sendKeyboard(sf::Keyboard::Key keyToCheck);
};

#endif