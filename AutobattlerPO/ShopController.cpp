#include "ShopController.h"
#include "Unit.h"
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <iostream>

ShopController::ShopController(int savedRank, std::vector<Unit*> savedTeam): UnitController(savedTeam) {
	shopRank = savedRank;
	selectedUnit = nullptr;
	selectedType = SHOP_UNIT;
	selectedIndex = -1;
}

ShopController::~ShopController() {
	for (int i = 0; i < shopUnits.size(); i++) {
		delete(shopUnits[i]);
	}
}

void ShopController::updatePositions() {
	for (int i = 0; i < shopUnits.size(); i++) {
		shopUnits[i]->setPosition((72 + 191) * i + 72, 72);
	}

	for (int i = 0; i < playerTeam.size(); i++) {
		playerTeam[i]->setPosition((72 + 191) * i + 72, 490);
	}
}

void ShopController::initializeShop(UNIT_MAP unitData, SPRITE_MAP &imageData) {
	UNIT_MAP::iterator it;

	for (it = unitData.begin(); it != unitData.end(); it++) {
		if (std::get<0>(it->second) > shopRank) {
			continue;
		}
		else {
			validUnits.push_back(it->first);
		}
	}

	processReroll(unitData, imageData);
	updatePositions();
	money = MAX_MONEY;
	printMoney();
}

void ShopController::processPurchase() {
	if (money >= PURCHASE_COST && selectedUnit != nullptr && selectedType == SHOP_UNIT) {
		for (int i = 0; i < playerTeam.size(); i++) {
			if (playerTeam[i]->getUnitType() == "NULL") {
				delete(playerTeam[i]);
				playerTeam[i] = selectedUnit;
				shopUnits.erase(shopUnits.begin() + selectedIndex);
				updatePositions();
				selectedUnit = nullptr;
				money -= 3;
				printMoney();
				break;
			}
		}
	}
}

void ShopController::processReroll(UNIT_MAP unitData, SPRITE_MAP& imageData) {
	if (money > 0) {
		for (int i = 0; i < shopUnits.size(); i++) {
			delete(shopUnits[i]);
		}
		shopUnits.clear();
		selectedUnit = nullptr;
		int randomMax;
		randomMax = validUnits.size();
		for (int i = 0; i < numberAllowedUnits; i++) {
			int randIndex = rand() % randomMax;
			shopUnits.push_back(new Unit(validUnits[randIndex], std::make_tuple(std::get<1>(unitData[validUnits[randIndex]]), std::get<2>(unitData[validUnits[randIndex]])), imageData, DEFAULT_UNIT_SIZE));
		}
		updatePositions();
		money -= 1;
		printMoney();
	}
}

void ShopController::processSell(SPRITE_MAP& imageData) {
	if (selectedType == TEAM_UNIT && selectedUnit != nullptr) {
		delete(selectedUnit);
		playerTeam.erase(playerTeam.begin() + selectedIndex);
		playerTeam.push_back(new Unit("NULL", std::make_tuple(0, 0), imageData, 0));
		updatePositions();
		selectedUnit = nullptr;
		money += 2;
		printMoney();
	}
}

std::vector<Unit*> ShopController::getPlayerTeam() {
	return playerTeam;
}

std::vector<Unit*> ShopController::getShopUnits() {
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

Unit* ShopController::getSelectedUnit() {
	return selectedUnit;
}

bool ShopController::teamIsEmpty() {
	if (playerTeam[0]->getUnitType() == "NULL") {
		return true;
	}
	return false;
}

void ShopController::setSelectedUnit(int index, int type) {
	if (type == 0) {
		selectedIndex = index;
		selectedUnit = playerTeam[index];
		selectedType = TEAM_UNIT;
	}
	else if (type == 1) {
		selectedIndex = index;
		selectedUnit = shopUnits[index];
		selectedType = SHOP_UNIT;
	}
	else {
		//type=-1
	}
}

void ShopController::giveMoney(int amount) {
	money += amount;
}

void ShopController::printMoney() {
	std::cout << "*MONEY* : " << money << "\n";
}