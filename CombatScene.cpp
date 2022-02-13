#include "CombatScene.h"
#include "ShopController.h"
#include "Unit.h"
#include <fstream>
#include <iterator>
#include <stdlib.h>

void startCombat() {
	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		//initialize random enemy team

		int randIndex = rand() % randomMax;
		enemyTeam.push_back(Unit(validUnits[randIndex], std::make_tuple(std::get<1>(unitData[validUnits[randIndex]]), std::get<2>(unitData[validUnits[randIndex]])), imageData));
	}

	window.clear();
	for (int i = 0; i < MAX_TEAM_SIZE; i++) {
		//draw sprites on screen
	}
}

void resolveEventQueue() {
	//copy the values of first units, we don't want to operate on the actual values since they reset between combats
	//NOTE: could also be done in a do while loop
	std::int currentHealth[2];
	if (playerTeam[0].getUnitType() != "NULL") && enemyTeam[0].getUnitType() != "NULL"){
		currentHealth[0] = playerTeam[0].baseHealth + playerTeam[0].modifierHealth;
		currentHealth[1] = enemyTeam[0].baseHealth + enemyTeam[0].modifierHealth;
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
		currentHealth[0] -= enemyTeam[j].baseAttack + enemyTeam[j].modifierAttack;
		currentHealth[1] -= playerTeam[i].baseAttack + playerTeam[i].modifierAttack;

		//if the unit dies, replace by the next team member if available
		if (currentHealth[0] <= 0) {
			if (playerTeam[i + 1].getUnitType() != "NULL") {
				i++;
				currentHealth[0]= playerTeam[i].baseHealth + playerTeam[i].modifierHealth;
			}
		}
		if (currentHealth[1] <= 0) {
			if (enemyTeam[j + 1].getUnitType() != "NULL") {
				j++;
				currentHealth[1] = enemyTeam[j].baseHealth + enemyTeam[j].modifierHealth;
			}
		}
	}

	if(currentHealth[0] <= 0) { 
		//player win
		std::count << "You WIN!";
		//money += 5;
	}
	else if (currentHealth[1] <= 0) {
		//enemy win
		std::count << "You lose.";
		//money += 1;
	}
	else {
		//stalemate
		std::count << "Stalemate!";
		//money += 3;
	}
}