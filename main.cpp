#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setTitle("SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("images/characters.png")) 
        return EXIT_FAILURE;

    sf::Sprite character;
    character.setTexture(texture);
    character.setTextureRect(sf::IntRect(0, 0, 32, 32));
    character.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

    float speedCharacter = 5;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                character.move(-speedCharacter, 0);
                character.setTextureRect(sf::IntRect(0, 32, 32, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                character.move(speedCharacter, 0);
                character.setTextureRect(sf::IntRect(0, 64, 32, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                character.move(0, -speedCharacter);
                character.setTextureRect(sf::IntRect(0, 96, 32, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                character.move(0, speedCharacter);
                character.setTextureRect(sf::IntRect(0, 0, 32, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            window.draw(character);

            window.display();
        }
    }

    return EXIT_SUCCESS;
}