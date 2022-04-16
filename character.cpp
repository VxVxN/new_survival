#include <SFML/Graphics.hpp>
#include <iostream>

enum Direction
{
    Up = 1,
    Down,
    Left,
    Right
};

class Character
{
private:
    const float maxFrame = 2;
    const float spriteSize = 32;

    sf::Sprite sprite;
    sf::Texture texture;
    float speedCharacter = 0.2;
    float currentFrame = 0;

    float updatePositionFrame();

public:
    Character(std::string filename);

    sf::Sprite getSprite();
    void setPosition(float x, float y);
    void move(Direction direction, float time);
};

Character::Character(std::string filename)
{
    texture.loadFromFile(filename);

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

sf::Sprite Character::getSprite()
{
    return sprite;
}

void Character::setPosition(float x, float y)
{
    sprite.setPosition(sf::Vector2f(x, y));
}

void Character::move(Direction direction, float time)
{
    float dy, dx;
    float positionFrame;
    switch (direction)
    {
    case Up:
        dy = -speedCharacter * time;
        sprite.move(0, dy);
        positionFrame = updatePositionFrame();
        sprite.setTextureRect(sf::IntRect(positionFrame, spriteSize * 3, spriteSize, spriteSize));
        break;
    case Down:
        dy = speedCharacter * time;
        sprite.move(0, dy);
        positionFrame = updatePositionFrame();
        sprite.setTextureRect(sf::IntRect(positionFrame, 0, spriteSize, spriteSize));
        break;
    case Left:
        dx = -speedCharacter * time;
        sprite.move(dx, 0);
        positionFrame = updatePositionFrame();
        sprite.setTextureRect(sf::IntRect(positionFrame, spriteSize, spriteSize, spriteSize));
        break;
    case Right:
        dx = speedCharacter * time;
        sprite.move(dx, 0);
        positionFrame = updatePositionFrame();
        sprite.setTextureRect(sf::IntRect(positionFrame, spriteSize * 2, spriteSize, spriteSize));
        break;
    default:
        break;
    }
}

float Character::updatePositionFrame()
{
    float positionFrame = currentFrame * spriteSize;
    if (maxFrame <= currentFrame)
    {
        currentFrame = 0;
    }
    currentFrame++;
    return positionFrame;
}