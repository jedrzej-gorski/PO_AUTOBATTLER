#ifndef SHOPCONTROLLER_H
#define SHOPCONTROLLER_H
#include "UnitController.h"

class ShopController : public UnitController {
	private:
		int money = 1;
		int shopRank = 0;
		int numberAllowedUnits = 4;
		std::vector<Unit*> shopUnits;
		Unit *selectedUnit;
		int selectedType;
		int selectedIndex;
	public:
		ShopController(int savedLevel, std::vector<Unit*> savedTeam);
		~ShopController();
		void updatePositions();
		void processReroll(UNIT_MAP unit_data, SPRITE_MAP &imageData);
		void processPurchase();
		void processSell(SPRITE_MAP &imageData);
		int getMoney();
		bool hasSelectedUnit();
		Unit* getSelectedUnit();
		bool teamIsEmpty();
		void removeShopUnit(int removeIndex);
		void initializeShop(UNIT_MAP unit_data, SPRITE_MAP &imageData);
		std::vector<Unit*> getPlayerTeam();
		std::vector<Unit*> getShopUnits();
		std::vector<std::string> getValidUnits();
		void setSelectedUnit(int index, int type);
		void giveMoney(int amount);
		void printMoney();
};
#endif

