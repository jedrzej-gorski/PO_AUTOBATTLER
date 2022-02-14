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

void ShopScene::processMouseInput(sf::Vector2i relativeMousePosition) {
	//searching for overlap in playerTeam and shopUnits
	std::vector<Unit> searchedUnits;
	searchedUnits = controller.getPlayerTeam();
	for (int i = 0; i < searchedUnits.size(); i++) {

	}
} 

//if true, change scene.
bool ShopScene::processKeyboard(sf::Keyboard::Key keyToCheck) {
	if (keyToCheck == sf::Keyboard::Key::R) {
		if (controller.getMoney() > 0) {
			controller.processReroll(unitData, imageData);
		}
		return false;
	}
	if (keyToCheck == sf::Keyboard::Key::S) {
		if (controller.hasSelectedUnit()) {
			//to update for actual sell implementation
			controller.processSell();
		}
		return false;
	}
	if (keyToCheck == sf::Keyboard::Key::Enter) {
		if (!controller.teamIsEmpty()) {
			return true;
		}
		return false;
	}
	if (keyToCheck == sf::Keyboard::Key::B) {
		if (controller.hasSelectedUnit()) {
			controller.processPurchase();
		}
		return false;
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