#include "window.cpp"
#include "character.cpp"
#include "map.cpp"

class Game
{
public:
    Game();
    ~Game();

    void update();
    void render();
    Window *getWindow();

    sf::Time getElapsed();
    void restartClock();

private:
    void _moveCharacter();
    Window _window;
    Character _character;
    Map _map;

    sf::Clock _clock;
    sf::Time _elapsed;
    float _pixelsPerSecond;
};

Game::Game() : _window("Survival", sf::Vector2u(1600, 1000)),
               _character("images/characters.png"),
               _map("images/map.png")
{
    _character.setPosition(_window.getWindowSize().x / 2, _window.getWindowSize().y / 2);

    _pixelsPerSecond = 400;
}

Game::~Game()
{
}

void Game::update()
{
    _window.update();
    _moveCharacter();
}

void Game::_moveCharacter()
{
    float speed = _elapsed.asSeconds() * _pixelsPerSecond;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _character.move(Left, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _character.move(Right, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _character.move(Up, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _character.move(Down, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _window.~Window();
    }
}

void Game::render()
{
    _window.clear();
    _map.render(_window.getRenderWindow());
    sf::Sprite sprite = _character.getSprite();
    _window.draw(sprite);
    _window.display();
}

sf::Time Game::getElapsed()
{
    return _elapsed;
}

void Game::restartClock()
{
    _elapsed = _clock.restart();
}

Window *Game::getWindow()
{
    return &_window;
}