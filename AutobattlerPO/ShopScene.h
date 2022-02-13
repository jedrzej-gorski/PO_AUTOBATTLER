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
		ShopScene(int savedLevel, std::vector<Unit> savedTeam, UNIT_MAP unitData, SPRITE_MAP &imageData);
		void resolveEventQueue();
};

#endif