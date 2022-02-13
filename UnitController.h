#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include <vector>
#include "Unit.h"
#include "Common.h"

class UnitController {
	protected:
		std::vector<Unit> playerTeam;
	public:
		UnitController(std::vector<Unit> savedTeam);
		virtual void step() = 0;
		virtual void initializeController() = 0;
};

#endif