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
public:
    Character(std::string filename);

    sf::Sprite getSprite();
    void setPosition(float x, float y);
    void move(Direction direction, float time);

private:
    const float _maxFrame = 2;
    const float _spriteSize = 32;

    sf::Sprite _sprite;
    sf::Texture _texture;
    float _speedCharacter = 40;
    float _currentFrame = 0;

    float _updatePositionFrame();
};

Character::Character(std::string filename)
{
    _texture.loadFromFile(filename);

    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

sf::Sprite Character::getSprite()
{
    return _sprite;
}

void Character::setPosition(float x, float y)
{
    _sprite.setPosition(sf::Vector2f(x, y));
}

void Character::move(Direction direction, float time)
{
    float dy, dx;
    float positionFrame;
    switch (direction)
    {
    case Up:
        dy = -_speedCharacter * time;
        _sprite.move(0, dy);
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize * 3, _spriteSize, _spriteSize));
        break;
    case Down:
        dy = _speedCharacter * time;
        _sprite.move(0, dy);
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, 0, _spriteSize, _spriteSize));
        break;
    case Left:
        dx = -_speedCharacter * time;
        _sprite.move(dx, 0);
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize, _spriteSize, _spriteSize));
        break;
    case Right:
        dx = _speedCharacter * time;
        _sprite.move(dx, 0);
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize * 2, _spriteSize, _spriteSize));
        break;
    default:
        break;
    }
}

float Character::_updatePositionFrame()
{
    float positionFrame = _currentFrame * _spriteSize;
    if (_maxFrame <= _currentFrame)
    {
        _currentFrame = 0;
    }
    _currentFrame++;
    return positionFrame;
}