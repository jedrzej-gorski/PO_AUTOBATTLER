#include "CombatScene.h"
#include "ShopController.h"
#include "Unit.h"
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <iostream>

CombatScene::CombatScene(std::vector<Unit> savedPlayerTeam, std::vector<std::string> savedValidUnits, SPRITE_MAP passedImageData, UNIT_MAP passedUnitData, sf::RenderWindow *passedWindow) {
	playerTeam = savedPlayerTeam;
	validUnits = savedValidUnits;
	imageData = passedImageData;
	unitData = passedUnitData;
	gameWindow = passedWindow;
}

std::tuple<std::vector<Unit>, std::vector<std::string>> CombatScene::getTransitionData() {
	std::vector<std::string> emptyVector;
	return std::make_tuple(playerTeam, emptyVector);
}

void CombatScene::startScene() {
	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		//initialize random enemy team
		int randomMax = validUnits.size();
		int randIndex = rand() % randomMax;
		enemyTeam.push_back(Unit(validUnits[randIndex], std::make_tuple(std::get<1>(unitData[validUnits[randIndex]]), std::get<2>(unitData[validUnits[randIndex]])), imageData, DEFAULT_UNIT_SIZE));
	}

	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		//putting enemy team where the shop was, might shift it a bit to the right to differentiate
		enemyTeam[i].setPosition((72 + 191) * i + 72, 72);
		//might not be needed. Player team is already there
		playerTeam[i].setPosition((72 + 191) * i + 72, 490);
	}
}

void CombatScene::drawSprites() {
	for (int i = 0; i < playerTeam.size(); i++) {
		if (playerTeam[i].getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(playerTeam[i].getNextTexture());
			int xPos = std::get<0>(playerTeam[i].getPosition());
			int yPos = std::get<1>(playerTeam[i].getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			gameWindow->draw(properSprite);
		}
	}
	for (int i = 0; i < enemyTeam.size(); i++) {
		if (enemyTeam[i].getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(enemyTeam[i].getNextTexture());
			int xPos = std::get<0>(playerTeam[i].getPosition());
			int yPos = std::get<1>(playerTeam[i].getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			gameWindow->draw(properSprite);
		}
	}
}

void CombatScene::resolveEventQueue() {
	//copy the values of first units, we don't want to operate on the actual values since they reset between combats
	//NOTE: could also be done in a do while loop
	int currentHealth[2];
	if (playerTeam[0].getUnitType() != "NULL" && enemyTeam[0].getUnitType() != "NULL"){
		currentHealth[0] = playerTeam[0].getUnitHealth();
		currentHealth[1] = enemyTeam[0].getUnitHealth();
	}

	//resolve unit abilities
	/*for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		if (playerTeam[i].getUnitType() != "NULL") {
			playerTeam[i].applyUnitEventEffects();
		}
		if (enemyTeam[i].getUnitType() != "NULL") {
			enemyTeam[i].applyUnitEventEffects();
		}
	}*/

	int i = 0, j = 0;

	while (currentHealth[0] > 0 && currentHealth[1] > 0) {
		//each unit lowers oponent's health by their attack
		currentHealth[0] -= enemyTeam[j].getUnitAttack();
		currentHealth[1] -= playerTeam[i].getUnitAttack();

		//placeholder for attack animations

		//if the unit dies, replace by the next team member if available
		if (currentHealth[0] <= 0) {
			if (playerTeam[i + 1].getUnitType() != "NULL") {
				i++;
				currentHealth[0]= playerTeam[i].getUnitHealth();
			}
		}
		if (currentHealth[1] <= 0) {
			if (enemyTeam[j + 1].getUnitType() != "NULL") {
				j++;
				currentHealth[1] = enemyTeam[j].getUnitHealth();
			}
		}
	}

	if(currentHealth[0] <= 0) { 
		//player win
		std::cout << "You WIN!";
		//money += 5;
	}
	else if (currentHealth[1] <= 0) {
		//enemy win
		std::cout << "You lose.";
		//money += 1;
	}
	else {
		//stalemate
		std::cout << "Stalemate!";
		//money += 3;
	}
}
