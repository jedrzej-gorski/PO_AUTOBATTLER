#ifndef SHOPCONTROLLER_H
#define SHOPCONTROLLER_H
#include "UnitController.h"

class ShopController : public UnitController {
	private:
		int money = 0;
		int shopRank = 0;
		int numberAllowedUnits = 4;
		std::vector<Unit> shopUnits;
		Unit *selectedUnit;
		int selectedType;
	public:
		ShopController(int savedLevel, std::vector<Unit> savedTeam);
		void updatePositions();
		void processReroll(UNIT_MAP unit_data, SPRITE_MAP &imageData);
		void processPurchase();
		void processSell();
		void removeShopUnit(int removeIndex);
		void initializeShop(UNIT_MAP unit_data, SPRITE_MAP &imageData);
		std::vector<Unit> getPlayerTeam();
		std::vector<Unit> getShopUnits();
		std::vector<std::string> getValidUnits();
};
#endif

