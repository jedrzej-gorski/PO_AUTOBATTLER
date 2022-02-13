#ifndef COMBATSCENE_H
#define COMBATSCENE_H

#include "Scene.h"
class CombatScene : public Scene {
	public:
		void startCombat();
		void resolveEventQueue();
	private:
		CombatScene();

};

#endif