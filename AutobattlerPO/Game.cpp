#include "Game.h"
#include "Scene.h"
#include "ShopScene.h"
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
	std::vector<Unit> emptyTeam(MAX_TEAM_SIZE, Unit("NULL", std::make_tuple(0, 0), graphicData));
	currentScene = ShopScene(1, emptyTeam, unitData, graphicData);
	currentScene.setBackground();
}
	