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
    Character() = default;
    Character(std::string filename);

    sf::Sprite getSprite();
    void setPosition(float x, float y);
    void move(Direction direction, float time);
    float x();
    float y();

private:
    float _x, _y;
    const float _maxFrame = 2;
    const float _spriteSize = 32;

    sf::Sprite _sprite;
    sf::Texture _texture;
    float _currentFrame = 0;

    float _updatePositionFrame();
};

Character::Character(std::string filename)
{
    if (!_texture.loadFromFile(filename))
    {
        throw "Failed to load character from file";
    }

    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

sf::Sprite Character::getSprite()
{
    return _sprite;
}

void Character::setPosition(float x, float y)
{
    _x = x;
    _y = y;
    _sprite.setPosition(sf::Vector2f(x, y));
}

void Character::move(Direction direction, float speed)
{
    float dy, dx;
    float positionFrame;
    switch (direction)
    {
    case Up:
        dy = -speed;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize * 3, _spriteSize, _spriteSize));
        break;
    case Down:
        dy = speed;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, 0, _spriteSize, _spriteSize));
        break;
    case Left:
        dx = -speed;
        _sprite.move(dx, 0);
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize, _spriteSize, _spriteSize));
        break;
    case Right:
        dx = speed;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize * 2, _spriteSize, _spriteSize));
        break;
    default:
        break;
    }

    _x += dx;
    _y += dy;
    _sprite.setPosition(_x, _y);
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

float Character::x()
{
    return _x;
}

float Character::y()
{
    return _y;
}