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

        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {

        }

        window.clear();
        window.display();
    }

    return 0;
}