#include "Game.h"
#include <fstream>

void initializeGame() {
	std::ifstream dataStream("data/unitData.txt");
	std::string unitName;
	int unitRank;

	if (dataStream) {
		while (!dataStream.eof()) {
			dataStream >> unitName >> unitRank;
			unitData[unitName] = unitRank;
		}
	}
}
	