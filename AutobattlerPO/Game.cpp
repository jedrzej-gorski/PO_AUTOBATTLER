#include "Game.h"
#include "Scene.h"
#include "ShopScene.h"
#include "CombatScene.h"
#include <fstream>

void Game::initializeGame() {
	std::ifstream dataStream("data/unitData.txt");
	std::string unitName;
	int unitRank, unitHealth, unitAttack;

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
	std::vector<Unit> emptyTeam(MAX_TEAM_SIZE, Unit("NULL", std::make_tuple(0, 0), graphicData, 0));
	currentScene = ShopScene(savedRank, emptyTeam, unitData, graphicData, gameWindow);
	currentScene.setBackground();
}

Game::Game(sf::RenderWindow* passedWindow) {
	turn = 0;
	savedRank = 1;
	currentPhase = SHOP;
	gameWindow = passedWindow;
}

void Game::passMouseInput(sf::Vector2i relativeMousePosition) {
	currentScene.processMouseInput(relativeMousePosition);
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
		currentScene = ShopScene(savedRank, std::get<0>(transitionData), unitData, graphicData, gameWindow);
		currentPhase = SHOP;
		currentScene.startScene();
	}
	//if in shop
	else {
		currentScene = CombatScene(std::get<0>(transitionData), std::get<1>(transitionData), graphicData, unitData, gameWindow);
		currentPhase = COMBAT;
		currentScene.startScene();
	}
}

void Game::drawScene() {
	currentScene.drawSprites();
}

void Game::sendKeyboard(sf::Keyboard::Key keyToCheck) {
	if (currentScene.processKeyboard(keyToCheck)) {
		changeScene();
	}
}