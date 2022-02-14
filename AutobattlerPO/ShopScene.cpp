#include "ShopScene.h"

ShopScene::ShopScene(int savedLevel, std::vector<Unit> savedTeam, UNIT_MAP passedUnitData, SPRITE_MAP passedImageData, int turn) : controller(ShopController(savedLevel, savedTeam, turn)) {
	imageData = passedImageData;
	unitData = passedUnitData;
	//initialize shop controller
	controller.initializeShop(unitData, imageData);
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