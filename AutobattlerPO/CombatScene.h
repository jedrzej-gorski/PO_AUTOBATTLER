#ifndef COMBATSCENE_H
#define COMBATSCENE_H
#include "UnitController.h"

#include "Scene.h"
class CombatScene : public Scene {
	private:
		std::vector<Unit*> playerTeam;
		std::vector<Unit*> enemyTeam;
		std::vector<std::string> validUnits;
		bool isDuringAnimation = false;
		//used for visual purposes only!! actual combat calculation happens all at once in resolveEventQueue()
		bool isDeadTeam[5] = { false };
		bool isDeadEnemy[5] = { false };
		//index, player_team?, xtarget, ytarget, waitforfinish?
		std::vector<std::tuple<int, bool, int, int, bool>> movementQueue;
		sf::Texture background;
	public:
		CombatScene(std::vector<Unit*> savedPlayerTeam, std::vector<std::string> savedValidUnits, SPRITE_MAP passedImageData, UNIT_MAP passedUnitData);
		~CombatScene();
		void startScene();
		void setBackground();
		void drawSprites(sf::RenderWindow &gameWindow);
		bool processKeyboard(sf::Keyboard::Key keyToCheck);
		void resolveEventQueue();
		void processMovements();
		std::tuple<std::vector<Unit*>, std::vector<std::string>> getTransitionData();

};

#endif
