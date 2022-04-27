#include <SFML/Graphics.hpp>
#include <iostream>

enum Direction
{
    None = 0,
    Up,
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
    Direction direction();
    bool isAlive();
    void update();

    int health();
    int hunger();
    int cold();

    void addHealth(int number);
    void addHunger(int number);
    void addCold(int number);

private:
    float _x, _y;
    float _dy, _dx;
    Direction _direction;
    const float _maxFrame = 2;
    const float _spriteSize = 32;

    int _health;
    int _hunger;
    int _cold;

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

    _health = 100;
    _hunger = 100;
    _cold = 100;
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
    float positionFrame;
    switch (direction)
    {
    case Up:
        _dy = -speed;
        _dx = 0;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize * 3, _spriteSize, _spriteSize));
        break;
    case Down:
        _dy = speed;
        _dx = 0;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, 0, _spriteSize, _spriteSize));
        break;
    case Left:
        _dx = -speed;
        _dy = 0;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize, _spriteSize, _spriteSize));
        break;
    case Right:
        _dx = speed;
        _dy = 0;
        positionFrame = _updatePositionFrame();
        _sprite.setTextureRect(sf::IntRect(positionFrame, _spriteSize * 2, _spriteSize, _spriteSize));
        break;
    default:
        break;
    }
    _direction = direction;
    _x += _dx;
    _y += _dy;
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

Direction Character::direction()
{
    return _direction;
}

bool Character::isAlive()
{
    if (_health <= 0)
    {
        return false;
    }
    return true;
}

int Character::health()
{
    return _health;
}

int Character::hunger()
{
    return _hunger;
}

int Character::cold()
{
    return _cold;
}

void Character::addHealth(int number)
{
    _health += number;
}

void Character::addHunger(int number)
{
    _hunger += number;
}

void Character::addCold(int number)
{
    _cold += number;
}

void Character::update()
{
    if (!isAlive())
    {
        return;
    }
    if (hunger() > 0)
    {
        addHunger(-10);
    }
    else
    {
        addHealth(-10);
    }
}
