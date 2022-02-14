#ifndef COMBATSCENE_H
#define COMBATSCENE_H
#include "UnitController.h"

#include "Scene.h"
class CombatScene : public Scene {
	private:
		std::vector<Unit> playerTeam;
		std::vector<Unit> enemyTeam;
		std::vector<std::string> validUnits;
		sf::RenderWindow* gameWindow;
	public:
		CombatScene(std::vector<Unit> savedPlayerTeam, std::vector<std::string> savedValidUnits, SPRITE_MAP passedImageData, UNIT_MAP passedUnitData, sf::RenderWindow *gameWindow);
		void startScene();
		void drawSprites();
		bool processKeyboard(sf::Keyboard::Key keyToCheck);
		void resolveEventQueue();
		std::tuple<std::vector<Unit>, std::vector<std::string>> getTransitionData();

};

#endif
