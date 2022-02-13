#include "ShopScene.h"

ShopScene::ShopScene(int savedLevel, std::vector<Unit> savedTeam, UNIT_MAP unitData, SPRITE_MAP &imageData) : controller(ShopController(savedLevel, savedTeam)) {
	//initialize shop controller
	controller.initializeShop(unitData, imageData);
}