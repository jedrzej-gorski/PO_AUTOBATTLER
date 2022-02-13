#ifndef SHOPCONTROLLER_H
#define SHOPCONTROLLER_H
#include "UnitController.h"

class ShopController : public UnitController {
	private:
		int money = 0;
		int shopRank = 0;
		int numberAllowedUnits = 0;
		std::vector<Unit> shopUnits;
		std::vector<std::string> validUnits;
		Unit *selectedUnit;
	public:
		ShopController(int savedLevel, std::vector<Unit> savedTeam);
		void step();
		void processReroll(UNIT_MAP unit_data, SPRITE_MAP &imageData);
		void processPurchase();
		void processSell();
		void removeShopUnit(int removeIndex);
		void initializeShop(std::vector<Unit> savedTeam, UNIT_MAP unit_data, SPRITE_MAP &imageData);
};
#endif

