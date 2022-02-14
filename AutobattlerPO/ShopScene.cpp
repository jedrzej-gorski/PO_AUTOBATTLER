#include "ShopScene.h"

ShopScene::ShopScene(int savedLevel, std::vector<Unit> savedTeam, UNIT_MAP passedUnitData, SPRITE_MAP passedImageData) : controller(ShopController(savedLevel, savedTeam)) {
	imageData = passedImageData;
	unitData = passedUnitData;
}

void ShopScene::startScene() {
	//initialize shop controller
	controller.initializeShop(unitData, imageData);
	std::vector<Unit> drawnUnits = controller.getPlayerTeam();
	for (int i = 0; i < drawnUnits.size(); i++) {
		if (drawnUnits[i].getUnitType() != "NULL") {
			//TODO: draw units
		}
	}
	drawnUnits = controller.getShopUnits();
	for (int i = 0; i < drawnUnits.size(); i++) {
		if (drawnUnits[i].getUnitType() != "NULL") {
			//TODO: draw units
		}
	}
}

void ShopScene::processMouseInput(sf::Vector2i relativeMousePosition, int mouseButton) {
	//TODO: whatever this is
	controller.processMousePosition(relativeMousePosition, mouseButton);
}

std::tuple<std::vector<Unit>, std::vector<std::string>> ShopScene::getTransitionData() {
	std::vector<Unit> savedPlayerTeam = controller.getPlayerTeam();
	std::vector<std::string> validUnitTypes = controller.getValidUnits();
	return std::make_tuple(savedPlayerTeam, validUnitTypes);
}