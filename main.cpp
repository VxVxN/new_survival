#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "character.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    Character character("images/characters.png");
    character.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    sf::Clock clock;
    while (window.isOpen())
    {
        float time = static_cast<float>(clock.restart().asMilliseconds());
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            character.move(Left, time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            character.move(Right, time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            character.move(Up, time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            character.move(Down, time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.draw(character.getSprite());

        window.display();
    }

    return EXIT_SUCCESS;
}