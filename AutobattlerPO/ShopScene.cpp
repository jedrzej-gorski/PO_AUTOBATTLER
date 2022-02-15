#include "ShopScene.h"

ShopScene::ShopScene(int savedLevel, std::vector<Unit*> savedTeam, UNIT_MAP passedUnitData, SPRITE_MAP passedImageData) : controller(ShopController(savedLevel, savedTeam)), Scene(passedUnitData, passedImageData) {}

void ShopScene::startScene() {
	//initialize shop controller
	controller.initializeShop(unitData, imageData);
	setBackground();
}

void ShopScene::processMouseInput(sf::Vector2i relativeMousePosition) {
	//searching for overlap in playerTeam and shopUnits
	//searching for overlap in playerTeam and shopUnits
	std::vector<Unit*> searchedUnits;
	searchedUnits = controller.getPlayerTeam();
	for (int i = 0; i < searchedUnits.size(); i++) {
		if ((std::get<0>(searchedUnits[i]->getPosition()) <= relativeMousePosition.x) && ((std::get<0>(searchedUnits[i]->getPosition()) + 191) >= relativeMousePosition.x) &&
			(std::get<1>(searchedUnits[i]->getPosition()) <= relativeMousePosition.y) && ((std::get<1>(searchedUnits[i]->getPosition()) + 191) >= relativeMousePosition.y)) {
			//overlap in playerTeam
			controller.setSelectedUnit(i, 0);
		}
	}
	searchedUnits = controller.getShopUnits();
	for (int i = 0; i < searchedUnits.size(); i++) {
		if ((std::get<0>(searchedUnits[i]->getPosition()) <= relativeMousePosition.x) && ((std::get<0>(searchedUnits[i]->getPosition()) + 191) >= relativeMousePosition.x) &&
			(std::get<1>(searchedUnits[i]->getPosition()) <= relativeMousePosition.y) && ((std::get<1>(searchedUnits[i]->getPosition()) + 191) >= relativeMousePosition.y)) {
			//overlap in shopUnits
			controller.setSelectedUnit(i, 1);
		}
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
			controller.processSell(imageData);
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
	return false;
}

std::tuple<std::vector<Unit*>, std::vector<std::string>> ShopScene::getTransitionData() {
	std::vector<Unit*> savedPlayerTeam = controller.getPlayerTeam();
	std::vector<std::string> validUnitTypes = controller.getValidUnits();
	return std::make_tuple(savedPlayerTeam, validUnitTypes);
}

void ShopScene::setBackground() {
	background.loadFromFile("./graphics/shop_bg.png");
}

void ShopScene::drawSprites(sf::RenderWindow &gameWindow) {
	Unit* selectedUnit = controller.getSelectedUnit();
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(background);
	gameWindow.draw(backgroundSprite);

	std::vector<Unit*> drawnUnits = controller.getPlayerTeam();
	for (int i = 0; i < drawnUnits.size(); i++) {
		if (drawnUnits[i]->getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(*(drawnUnits[i]->getNextTexture()));
			int xPos = std::get<0>(drawnUnits[i]->getPosition());
			int yPos = std::get<1>(drawnUnits[i]->getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			if (drawnUnits[i] == selectedUnit) {
				properSprite.setColor(sf::Color(255, 255, 255, 128)); // half transparent
			}
			sf::RectangleShape healthShape(sf::Vector2f(11, 11));
			sf::RectangleShape attackShape(sf::Vector2f(11, 11));
			healthShape.setFillColor(sf::Color(255, 0, 0));
			for (int j = 0; j < drawnUnits[i]->getUnitHealth(); j++) {
				healthShape.setPosition(sf::Vector2f(16 * j + xPos, yPos + 191 - 11));
				gameWindow.draw(healthShape);
			}
			attackShape.setFillColor(sf::Color(0, 0, 255));
			for (int j = 0; j < drawnUnits[i]->getUnitAttack(); j++) {
				attackShape.setPosition(sf::Vector2f(xPos + 191 - 11 - (16 * j), yPos + 191 - 11));
				gameWindow.draw(attackShape);
			}
			gameWindow.draw(properSprite);
		}
	}
	drawnUnits = controller.getShopUnits();
	for (int i = 0; i < drawnUnits.size(); i++) {
		if (drawnUnits[i]->getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(*(drawnUnits[i]->getNextTexture()));
			int xPos = std::get<0>(drawnUnits[i]->getPosition());
			int yPos = std::get<1>(drawnUnits[i]->getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			if (drawnUnits[i] == selectedUnit) {
				properSprite.setColor(sf::Color(255, 255, 255, 128)); // half transparent
			}
			sf::RectangleShape healthShape(sf::Vector2f(11, 11));
			sf::RectangleShape attackShape(sf::Vector2f(11, 11));
			healthShape.setFillColor(sf::Color(255, 0, 0));
			for (int j = 0; j < drawnUnits[i]->getUnitHealth(); j++) {
				healthShape.setPosition(sf::Vector2f(16 * j + xPos, yPos + 191 - 11));
				gameWindow.draw(healthShape);
			}
			attackShape.setFillColor(sf::Color(0, 0, 255));
			for (int j = 0; j < drawnUnits[i]->getUnitAttack(); j++) {
				attackShape.setPosition(sf::Vector2f(xPos + 191 - 11 - (16 * j), yPos + 191 - 11));
				gameWindow.draw(attackShape);
			}
			gameWindow.draw(properSprite);
			gameWindow.draw(properSprite);
		}
	}
}