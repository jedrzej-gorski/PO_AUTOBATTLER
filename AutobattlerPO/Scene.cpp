#include "Scene.h"
#include <SFML/Graphics.hpp>

Scene::Scene(UNIT_MAP passedUnitData, SPRITE_MAP passedImageData) {
	unitData = passedUnitData;
	imageData = passedImageData;
}

std::tuple<std::vector<Unit*>, std::vector<std::string>> Scene::getTransitionData() {
	std::vector<Unit*> emptyVector1;
	std::vector<std::string> emptyVector2;
	return std::make_tuple(emptyVector1, emptyVector2);
}
bool Scene::processKeyboard(sf::Keyboard::Key keyToCheck) {
	return false;
}