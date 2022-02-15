#include "ShopScene.h"

ShopScene::ShopScene(int savedLevel, std::vector<Unit> savedTeam, UNIT_MAP passedUnitData, SPRITE_MAP passedImageData, sf::RenderWindow *passedWindow) : controller(ShopController(savedLevel, savedTeam)) {
	imageData = passedImageData;
	unitData = passedUnitData;
	gameWindow = passedWindow;
}

void ShopScene::startScene() {
	//initialize shop controller
	controller.initializeShop(unitData, imageData);
}

void ShopScene::processMouseInput(sf::Vector2i relativeMousePosition, int mouseButton) {
	//searching for overlap in playerTeam and shopUnits
	std::vector<Unit> searchedUnits;
	searchedUnits = controller.getPlayerTeam();
	for (int i = 0; i < searchedUnits.size(); i++) {
		if ((std::get<1>(searchedUnits[i].getPosition()) >= relativeMousePosition[0]) && ((std::get<1>(searchedUnits[i].getPosition()) <= relativeMousePosition[0]) + 191)
			(std::get<1>(searchedUnits[i].getPosition()) >= relativeMousePosition[1]) && ((std::get<1>(searchedUnits[i].getPosition()) <= relativeMousePosition[1]) + 191)) {
			//overlap in playerTeam
			ShopScene.setSelectedUnit(i, 0);
		}
	}
	searchedUnits = controller.getShopUnits();
	for (int i = 0; i < searchedUnits.size(); i++) {
		if ((std::get<1>(searchedUnits[i].getPosition()) >= relativeMousePosition[0]) && ((std::get<1>(searchedUnits[i].getPosition()) <= relativeMousePosition[0]) + 191)
			(std::get<1>(searchedUnits[i].getPosition()) >= relativeMousePosition[1]) && ((std::get<1>(searchedUnits[i].getPosition()) <= relativeMousePosition[1]) + 191)) {
			//overlap in shopUnits
			ShopScene.setSelectedUnit(i, 1);
		}
	}


} 

std::tuple<std::vector<Unit>, std::vector<std::string>> ShopScene::getTransitionData() {
	std::vector<Unit> savedPlayerTeam = controller.getPlayerTeam();
	std::vector<std::string> validUnitTypes = controller.getValidUnits();
	return std::make_tuple(savedPlayerTeam, validUnitTypes);
}

void ShopScene::drawSprites() {
	std::vector<Unit> drawnUnits = controller.getPlayerTeam();
	for (int i = 0; i < drawnUnits.size(); i++) {
		if (drawnUnits[i].getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(drawnUnits[i].getNextTexture());
			int xPos = std::get<0>(drawnUnits[i].getPosition());
			int yPos = std::get<1>(drawnUnits[i].getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			gameWindow->draw(properSprite);
		}
	}
	drawnUnits = controller.getShopUnits();
	for (int i = 0; i < drawnUnits.size(); i++) {
		if (drawnUnits[i].getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(drawnUnits[i].getNextTexture());
			int xPos = std::get<0>(drawnUnits[i].getPosition());
			int yPos = std::get<1>(drawnUnits[i].getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			gameWindow->draw(properSprite);
		}
	}
}