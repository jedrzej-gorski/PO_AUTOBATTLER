#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include <vector>
#include "Unit.h"
#include "Common.h"

class UnitController {
	protected:
		std::vector<Unit> playerTeam;
		std::vector<Unit> enemyTeam;
	public:
		UnitController(std::vector<Unit> savedTeam);
		//virtual void step() = 0;
};

#endif
