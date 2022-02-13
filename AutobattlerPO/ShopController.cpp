#include "ShopController.h"
#include "Unit.h"
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <time.h>

ShopController::ShopController(int savedRank, std::vector<Unit> savedTeam): UnitController(savedTeam) {
	shopRank = savedRank;
	selectedUnit = nullptr;
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
	money = MAX_MONEY;
}

void ShopController::processPurchase() {
	if (money > PURCHASE_COST) {
		for (int i = 0; i < MAX_TEAM_SIZE; i++) {
			if (playerTeam[i].getUnitType() == "NULL") {
				playerTeam[i] = *selectedUnit;
				removeShopUnit(i);
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
	int randomMax;
	randomMax = validUnits.size();
	for (int i = 0; i < numberAllowedUnits; i++) {
		int randIndex = rand() % randomMax;
		shopUnits.push_back(Unit(validUnits[randIndex], std::make_tuple(std::get<1>(unitData[validUnits[randIndex]]), std::get<2>(unitData[validUnits[randIndex]])), imageData));
	}
	money -= 1;
}

void ShopController::processSell() {
	
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
