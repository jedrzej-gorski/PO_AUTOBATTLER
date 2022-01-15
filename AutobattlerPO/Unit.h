#ifndef UNIT_H
#define UNIT_H

#include "Common.h"
#include "Token.h"

class Unit : public Token {
	private:
		std::string type;
		int baseHealth;
		int baseAttack;
		int modifierHealth;
		int modifierAttack;
	public:
		Unit(std::string unitType, std::tuple<int, int> statSpread, SPRITE_MAP& imageData);
		void addModifierAttack(int value);
		void addModifierHealth(int value);
		void addBaseAttack(int value);
		void addBaseHealth(int value);
		void resetModifiers();
		gameEvent applyUnitEventEffects(unitEvent processedEvent);
		std::string getUnitType();
};

#endif