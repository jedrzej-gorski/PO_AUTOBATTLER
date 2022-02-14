#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "Autobattler");
    Game gameInstance;
    gameInstance.initializeGame();

    sf::Clock clock;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            gameInstance.passMouseInput(sf::Mouse::getPosition(window), LEFT_CLICK);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            gameInstance.passMouseInput(sf::Mouse::getPosition(window), RIGHT_CLICK);
        }

        window.clear();
        window.display();
    }

    return 0;
}