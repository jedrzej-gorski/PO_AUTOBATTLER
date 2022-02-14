#include "ShopController.h"
#include "Unit.h"
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <time.h>

ShopController::ShopController(int savedRank, std::vector<Unit> savedTeam): UnitController(savedTeam) {
	shopRank = savedRank;
	selectedUnit = nullptr;
	selectedType = NONE;
}

void ShopController::updatePositions() {
	for (int i = 0; i < numberAllowedUnits; i++) {
		shopUnits[i].setPosition((72 + 191) * i + 72, 72);
	}

	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		playerTeam[i].setPosition((72 + 191) * i + 72, 490);
	}
}

void ShopController::initializeShop(UNIT_MAP unitData, SPRITE_MAP &imageData) {
	UNIT_MAP::iterator it;

	for (it = unitData.begin(); it != unitData.end(); it++) {
		if (std::get<0>(it->second) > shopRank) {
			break;
		}
		else {
			validUnits.push_back(it->first);
		}
	}

	processReroll(unitData, imageData);
	updatePositions();
	money = MAX_MONEY;
}

void ShopController::processPurchase() {
	if (money > PURCHASE_COST && selectedType == SHOP_UNIT) {
		for (int i = 0; i < MAX_TEAM_SIZE; i++) {
			if (playerTeam[i].getUnitType() == "NULL") {
				playerTeam[i] = *selectedUnit;
				removeShopUnit(i);
				updatePositions();
				selectedUnit = nullptr;
				break;
			}
		}
	}
}

void ShopController::removeShopUnit(int removeIndex) {
	shopUnits.erase(shopUnits.begin() + removeIndex);
}

void ShopController::processReroll(UNIT_MAP unitData, SPRITE_MAP& imageData) {
	shopUnits.clear();
	selectedUnit = nullptr;
	int randomMax;
	randomMax = validUnits.size();
	for (int i = 0; i < numberAllowedUnits; i++) {
		int randIndex = rand() % randomMax;
		shopUnits.push_back(Unit(validUnits[randIndex], std::make_tuple(std::get<1>(unitData[validUnits[randIndex]]), std::get<2>(unitData[validUnits[randIndex]])), imageData, DEFAULT_UNIT_SIZE));
	}
	updatePositions();
	money -= 1;
}

void ShopController::processSell() {
	if (selectedType == TEAM_UNIT) {
		for (int i = 0; i < MAX_TEAM_SIZE; i++) {
			if (playerTeam[i].getUnitType() != "NULL") {
				//if (sf::Mouse::GetPosition(window).x == unitSprite.getPosition().x &&
				//	  sf::Mouse::GetPosition(window).y == unitSprite.getPosition().y){
				//		playerTeam[i]=0;
				//		money++;
				//}
				//check if mouse hovers over a unit
			}
		}
	}
}

std::vector<Unit> ShopController::getPlayerTeam() {
	return playerTeam;
}

std::vector<Unit> ShopController::getShopUnits() {
	return shopUnits;
}

std::vector<std::string> ShopController::getValidUnits() {
	return validUnits;
}

int ShopController::getMoney() {
	return money;
}

bool ShopController::hasSelectedUnit() {
	if (selectedUnit == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

bool ShopController::teamIsEmpty() {
	if (playerTeam[0].getUnitType() == "NULL") {
		return true;
	}
	return false;
}
