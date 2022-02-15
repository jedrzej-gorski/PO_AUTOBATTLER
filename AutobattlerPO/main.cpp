#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1440, 810), "Autobattler");
    Game gameInstance = Game(&window);
    gameInstance.initializeGame();

    sf::Clock clock;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    gameInstance.passMouseInput(sf::Mouse::getPosition(window));
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                gameInstance.sendKeyboard(event.key.code);
            }
        }


        window.clear();
        gameInstance.drawScene();
        window.display();
    }

    return 0;
}