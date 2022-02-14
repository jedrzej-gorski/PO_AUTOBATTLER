#ifndef COMBATSCENE_H
#define COMBATSCENE_H
#include "UnitController.h"

#include "Scene.h"
class CombatScene : public Scene {
	private:
		std::vector<Unit> playerTeam;
		std::vector<Unit> enemyTeam;
		std::vector<std::string> validUnits;
	public:
		CombatScene(std::vector<Unit> savedPlayerTeam, std::vector<std::string> savedValidUnits, SPRITE_MAP passedImageData, UNIT_MAP passedUnitData);
		void startCombat();
		void resolveEventQueue();

};

#endif
