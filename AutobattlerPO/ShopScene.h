#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "Scene.h"
#include "Unit.h"

#include <vector>

class ShopScene : public Scene {
	private:
		int selectedUnit;
		ShopController controller;
	public:
		ShopScene();
		void resolveEventQueue();
};

#endif