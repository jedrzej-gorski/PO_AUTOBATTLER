#include "Game.h"
#include "Scene.h"
#include "ShopScene.h"
#include "CombatScene.h"
#include <fstream>

void Game::initializeGame() {
	std::ifstream dataStream("data/unitData.txt");
	std::string unitName;
	int unitRank, unitHealth, unitAttack;
	turn = 0;
	savedRank = 1;
	currentPhase = SHOP;

	//loading unit data
	if (dataStream) {
		while (!dataStream.eof()) {
			dataStream >> unitName >> unitRank >> unitHealth >> unitAttack;
			//pack into tuple and map to unitName
			unitData[unitName] = std::make_tuple(unitRank, unitHealth, unitAttack);
		}
	}

	//declaring a vector of empty units
	//WARNING: watch out for processing graphics data on a unit type that doesn't exist
	std::vector<Unit> emptyTeam(MAX_TEAM_SIZE, Unit("NULL", std::make_tuple(0, 0), graphicData));
	currentScene = ShopScene(savedRank, emptyTeam, unitData, graphicData);
	currentScene.setBackground();
}

Game::Game(sf::RenderWindow* passedWindow) {
	window = passedWindow;
}

void Game::passMouseInput(sf::Vector2i relativeMousePosition, int mouseButton) {
	currentScene.processMouseInput(relativeMousePosition, mouseButton);
}

void Game::changeScene() {
	//vector with player team and valid units for random generation (if applicable, as CombatScene does NOT pass validUnits, the second vector in the tuple is empty)
	std::tuple<std::vector<Unit>, std::vector<std::string>> transitionData = currentScene.getTransitionData();
	//if in combat
	if (currentPhase) {
		turn++;
		//if even turn and saved rank < 3 (max rank), increase rank
		if (turn % 2 == 0 && savedRank < 3) {
			savedRank++;
		}
		currentScene = ShopScene(savedRank, std::get<0>(transitionData), unitData, graphicData);
		currentPhase = SHOP;
		window->clear();
		currentScene.startScene();
	}
	//if in shop
	else {
		currentScene = CombatScene(std::get<0>(transitionData), std::get<1>(transitionData), graphicData, unitData);
		currentPhase = COMBAT;
		window->clear();
		currentScene.startScene();
	}
}

