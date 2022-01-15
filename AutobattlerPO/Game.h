#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "Scene.h"
#include <map>

class Game {
	private:
		Scene currentScene;
		SPRITE_MAP graphicData;
		UNIT_MAP unitData;
	public:
		Game();
		void changeScene();
		void initializeGame();
		void stepGame();
};

#endif