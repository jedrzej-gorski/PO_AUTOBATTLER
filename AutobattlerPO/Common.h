#ifndef COMMON_H
#define COMMON_H

#define MAX_MONEY 15
#define PURCHASE_COST 3
#define MAX_TEAM_SIZE 5
#define LEFT_CLICK 0
#define RIGHT_CLICK 1
#define SHOP 0
#define COMBAT 1
#define TEAM_UNIT 0
#define SHOP_UNIT 1
#define DEFAULT_UNIT_SIZE 191

#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <SFML/Graphics.hpp>


typedef std::string animationTag;
typedef std::string gameEvent;
typedef std::string unitEvent;

typedef std::map<std::string, std::tuple<int, int, int>> UNIT_MAP;
typedef std::map<std::string, std::vector<sf::Texture>> SPRITE_MAP;
typedef std::map<animationTag, std::tuple<int, int>> ANIMATION_MAP;


#endif