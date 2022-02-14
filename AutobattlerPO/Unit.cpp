#include "Unit.h"

Unit::Unit(std::string unitType, std::tuple<int, int> statSpread, SPRITE_MAP &imageData): Token(unitType, 0, 0, imageData) {
	type = unitType;
	baseHealth = std::get<0>(statSpread);
	baseAttack = std::get<1>(statSpread);
	modifierHealth = 0;
	modifierAttack = 0;
}

void Unit::addModifierAttack(int value) {
	modifierAttack += value;
}

void Unit::addModifierHealth(int value) {
	modifierHealth += value;
}

void Unit::addBaseAttack(int value) {
	baseAttack += value;
}

void Unit::addBaseHealth(int value) {
	baseHealth += value;
}

void Unit::resetModifiers() {
	modifierAttack = 0;
	modifierHealth = 0;
}

std::string Unit::getUnitType() {
	return type;
}

int Unit::getUnitHealth() {
	return baseHealth + modifierHealth;
}

int Unit::getUnitAttack() {
	return baseAttack + modifierAttack;
}