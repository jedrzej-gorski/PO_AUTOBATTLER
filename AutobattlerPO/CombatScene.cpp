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
	background.loadFromFile("./graphics/battle_bg.png");
}

void CombatScene::processMovements() {
	int index = 0;
	bool mustWait = 0;
	while (movementQueue.size() != index && !mustWait) {
		std::tuple<int, bool, int, int, bool> newMovement = movementQueue[index];
		int unitIndex = std::get<0>(newMovement);
		bool team = std::get<1>(newMovement);
		int target_x = std::get<2>(newMovement);
		int target_y = std::get<3>(newMovement);
		//fade_out
		if (target_x == -1 && target_y == -1) {
			mustWait = 0;
			movementQueue.erase(movementQueue.begin() + index);
			if (team) {
				isDeadTeam[unitIndex] = true;
			}
			else {
				isDeadEnemy[unitIndex] = true;
			}
			continue;
		}
		else {
			//actual movement. if movement performed, keep going until end of vector
			if (team) {
				int current_x = std::get<0>(playerTeam[unitIndex]->getPosition());
				int current_y = std::get<1>(playerTeam[unitIndex]->getPosition());
				float x_step = 0, y_step;
				if (current_x == target_x && current_y == target_y) {
					mustWait = 0;
					movementQueue.erase(movementQueue.begin() + index);
					continue;
				}
				else {
					if (target_y - current_y > 0) {
						y_step = 1;
					}
					else {
						y_step = -1;
					}
					playerTeam[unitIndex]->setPosition(current_x + x_step, current_y + y_step);
					mustWait = std::get<4>(newMovement);
					isDuringAnimation = true;
					index++;
				}
			}
			else {
				int current_x = std::get<0>(enemyTeam[unitIndex]->getPosition());
				int current_y = std::get<1>(enemyTeam[unitIndex]->getPosition());
				float x_step = 0, y_step;
				if (current_x == target_x && current_y == target_y) {
					mustWait = 0;
					movementQueue.erase(movementQueue.begin() + index);
					continue;
				}
				else {
					if (target_y - current_y > 0) {
						y_step = 1;
					}
					else {
						y_step = -1;
					}
					enemyTeam[unitIndex]->setPosition(current_x + x_step, current_y + y_step);
					mustWait = std::get<4>(newMovement);
					isDuringAnimation = true;
					index++;
				}
			}
		}
	}
	isDuringAnimation = false;
}

void CombatScene::drawSprites(sf::RenderWindow &gameWindow) {
	processMovements();
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

			if (isDeadTeam[i]) {
				properSprite.setColor(sf::Color(255, 255, 255, 64));
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

			if (isDeadEnemy[i]) {
				properSprite.setColor(sf::Color(255, 255, 255, 64));
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
		std::tuple<int, bool, int, int, bool> newMovement = std::make_tuple(j, 0, std::get<0>(enemyCopy[j]->getPosition()), std::get<1>(enemyCopy[j]->getPosition()) + 50, 0);
		movementQueue.push_back(newMovement);
		currentHealth[1] -= playerCopy[i]->getUnitAttack();
		newMovement = std::make_tuple(i, 1, std::get<0>(playerCopy[i]->getPosition()), std::get<1>(playerCopy[i]->getPosition()) - 50, 1);
		movementQueue.push_back(newMovement);

		//move units back into their respective spots
		newMovement = std::make_tuple(j, 0, std::get<0>(enemyCopy[j]->getPosition()), std::get<1>(enemyCopy[j]->getPosition()), 0);
		movementQueue.push_back(newMovement);
		newMovement = std::make_tuple(i, 1, std::get<0>(playerCopy[i]->getPosition()), std::get<1>(playerCopy[i]->getPosition()), 1);
		movementQueue.push_back(newMovement);

		//placeholder for attack animations

		//if the unit dies, replace by the next team member if available
		if (currentHealth[0] <= 0) {
			//not a movement per se, just a signal to fade out the unit
			newMovement = std::make_tuple(i, 1, -1, -1, 1);
			movementQueue.push_back(newMovement);
			if (i + 1 < MAX_TEAM_SIZE && playerCopy[i + 1]->getUnitType() != "NULL") {
				i++;
				currentHealth[0]= playerCopy[i]->getUnitHealth();
			}
			else {}
		}
		if (currentHealth[1] <= 0) {
			newMovement = std::make_tuple(j, 0, -1, -1, 1);
			movementQueue.push_back(newMovement);
			if (j + 1 < MAX_TEAM_SIZE && enemyCopy[j + 1]->getUnitType() != "NULL") {
				j++;
				currentHealth[1] = enemyCopy[j]->getUnitHealth();
			}
		}
	}

	if(currentHealth[0] <= 0 && currentHealth[1] <= 0) {
		//stalemate
		std::cout << "Stalemate!\n";
		//money += 3;
	}
	else if (currentHealth[1] <= 0) {
		//player win
		std::cout << "You WIN!\n";
		//money += 5;
	}
	else {
		//player loss
		std::cout << "You Lose!\n";
		//money += 1;
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
