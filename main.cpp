#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "Autobattler");

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

        if (sf::Mouse::is:ButtonPressed(sf::Mouse::Right))
        {

        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}