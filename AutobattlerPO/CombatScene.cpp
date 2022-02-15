#include "CombatScene.h"
#include "ShopController.h"
#include "Unit.h"
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <iostream>

CombatScene::CombatScene(std::vector<Unit*> savedPlayerTeam, std::vector<std::string> savedValidUnits, SPRITE_MAP passedImageData, UNIT_MAP passedUnitData) : Scene(passedUnitData, passedImageData) {
	playerTeam = savedPlayerTeam;
	validUnits = savedValidUnits;
}

CombatScene::~CombatScene() {
	for (int i = 0; i < enemyTeam.size(); i++) {
		delete(enemyTeam[i]);
	}

}
//TODO: fix that one memory leak
std::tuple<std::vector<Unit*>, std::vector<std::string>> CombatScene::getTransitionData() {
	std::vector<std::string> emptyVector;
	return std::make_tuple(playerTeam, emptyVector);
}

void CombatScene::startScene() {
	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		//initialize random enemy team
		int randomMax = validUnits.size();
		int randIndex = rand() % randomMax;
		enemyTeam.push_back(new Unit(validUnits[randIndex], std::make_tuple(std::get<1>(unitData[validUnits[randIndex]]), std::get<2>(unitData[validUnits[randIndex]])), imageData, DEFAULT_UNIT_SIZE));
	}

	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		//putting enemy team where the shop was, might shift it a bit to the right to differentiate
		enemyTeam[i]->setPosition((72 + 191) * i + 72, 72);
		//might not be needed. Player team is already there
		playerTeam[i]->setPosition((72 + 191) * i + 72, 490);
	}

	setBackground();
	resolveEventQueue();
}

void CombatScene::setBackground() {
	background.loadFromFile("../graphics/battle_bg.png");
}

void CombatScene::drawSprites(sf::RenderWindow &gameWindow) {
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(background);
	gameWindow.draw(backgroundSprite);

	for (int i = 0; i < playerTeam.size(); i++) {
		if (playerTeam[i]->getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(*(playerTeam[i]->getNextTexture()));
			int xPos = std::get<0>(playerTeam[i]->getPosition());
			int yPos = std::get<1>(playerTeam[i]->getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			sf::RectangleShape healthShape(sf::Vector2f(11, 11));
			sf::RectangleShape attackShape(sf::Vector2f(11, 11));
			healthShape.setFillColor(sf::Color(255, 0, 0));
			for (int j = 0; j < playerTeam[i]->getUnitHealth(); j++) {
				healthShape.setPosition(sf::Vector2f(16 * j + xPos, yPos + 191 - 11));
				gameWindow.draw(healthShape);
			}
			attackShape.setFillColor(sf::Color(0, 0, 255));
			for (int j = 0; j < playerTeam[i]->getUnitAttack(); j++) {
				attackShape.setPosition(sf::Vector2f(xPos + 191 - 11 - (16 * j), yPos + 191 - 11));
				gameWindow.draw(attackShape);
			}
			gameWindow.draw(properSprite);
		}
	}
	for (int i = 0; i < enemyTeam.size(); i++) {
		if (enemyTeam[i]->getUnitType() != "NULL") {
			sf::Sprite properSprite;
			properSprite.setTexture(*(enemyTeam[i]->getNextTexture()));
			int xPos = std::get<0>(enemyTeam[i]->getPosition());
			int yPos = std::get<1>(enemyTeam[i]->getPosition());
			properSprite.setPosition(sf::Vector2f(xPos, yPos));
			sf::RectangleShape healthShape(sf::Vector2f(11, 11));
			sf::RectangleShape attackShape(sf::Vector2f(11, 11));
			healthShape.setFillColor(sf::Color(255, 0, 0));
			for (int j = 0; j < enemyTeam[i]->getUnitHealth(); j++) {
				healthShape.setPosition(sf::Vector2f(16 * j + xPos, yPos + 191 - 11));
				gameWindow.draw(healthShape);
			}
			attackShape.setFillColor(sf::Color(0, 0, 255));
			for (int j = 0; j < enemyTeam[i]->getUnitAttack(); j++) {
				attackShape.setPosition(sf::Vector2f(xPos + 191 - 11 - (16 * j), yPos + 191 - 11));
				gameWindow.draw(attackShape);
			}
			gameWindow.draw(properSprite);
		}
	}
}

void CombatScene::resolveEventQueue() {
	//copy the values of first units, we don't want to operate on the actual values since they reset between combats
	//NOTE: could also be done in a do while loop
	std::vector<Unit*> playerCopy = playerTeam;
	std::vector<Unit*> enemyCopy = enemyTeam;
	int currentHealth[2];
	if (playerCopy[0]->getUnitType() != "NULL" && enemyCopy[0]->getUnitType() != "NULL"){
		currentHealth[0] = playerCopy[0]->getUnitHealth();
		currentHealth[1] = enemyCopy[0]->getUnitHealth();
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
		currentHealth[0] -= enemyCopy[j]->getUnitAttack();
		currentHealth[1] -= playerCopy[i]->getUnitAttack();

		//placeholder for attack animations

		//if the unit dies, replace by the next team member if available
		if (currentHealth[0] <= 0) {
			if (i + 1 < MAX_TEAM_SIZE && playerCopy[i + 1]->getUnitType() != "NULL") {
				i++;
				currentHealth[0]= playerCopy[i]->getUnitHealth();
			}
		}
		if (currentHealth[1] <= 0) {
			if (i + 1 < MAX_TEAM_SIZE && enemyCopy[j + 1]->getUnitType() != "NULL") {
				j++;
				currentHealth[1] = enemyCopy[j]->getUnitHealth();
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
	//std::cout << "hey";
}

bool CombatScene::processKeyboard(sf::Keyboard::Key keyToCheck) {
	if (keyToCheck == sf::Keyboard::Key::Enter) {
		return true;
	}
	else {
		return false;
	}
}
