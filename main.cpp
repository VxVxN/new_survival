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

    float speedCharacter = 0.2;
    float spriteSize = 32;
    float currentFrame = 0;
    float maxFrame = 2;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            float dx = -speedCharacter * time;
            character.move(dx, 0);
            float positionFrame = currentFrame * spriteSize;
            if (maxFrame <= currentFrame) {
                currentFrame = 0;
            }
            currentFrame++;
            character.setTextureRect(sf::IntRect(positionFrame, spriteSize, spriteSize, spriteSize));
        
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            float dx = speedCharacter * time;
            character.move(dx, 0);
            float positionFrame = currentFrame * spriteSize;
            if (maxFrame <= currentFrame) {
                currentFrame = 0;
            }
            currentFrame++;
            character.setTextureRect(sf::IntRect(positionFrame, spriteSize*2, spriteSize, spriteSize));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            float dy = -speedCharacter * time;
            character.move(0, dy);
            float positionFrame = currentFrame * spriteSize;
            if (maxFrame <= currentFrame) {
                currentFrame = 0;
            }
            currentFrame++;
            character.setTextureRect(sf::IntRect(positionFrame, spriteSize*3, spriteSize, spriteSize));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            float dy = speedCharacter * time;
            character.move(0, dy);
            float positionFrame = currentFrame * spriteSize;
            if (maxFrame <= currentFrame) {
                currentFrame = 0;
            }
            currentFrame++;
            character.setTextureRect(sf::IntRect(positionFrame, 0, spriteSize, spriteSize));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.draw(character);

        window.display();
    }

    return EXIT_SUCCESS;
}