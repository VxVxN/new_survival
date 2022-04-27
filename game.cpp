#include "window.cpp"
#include "character.cpp"
#include "map.cpp"
#include "camera.cpp"
#include "textbox.cpp"

class Game
{
public:
    Game();
    ~Game();

    void update();
    void render();
    void handleInput();
    Window *getWindow();

    sf::Time getElapsed();
    void restartClock();

private:
    void _moveCharacter();
    void interactionWithMap();

    Window _window;
    Character _character;
    Direction _characterDirection;
    Map _map;
    Camera _camera;
    Textbox _textbox;

    sf::Clock _clock;
    sf::Time _elapsed;
    sf::Time _globTime;
    int _lastSecond;
    float _pixelsPerSecond;
};

Game::Game() : _window("Survival", sf::Vector2u(1600, 1000)),
               _character("images/characters.png"),
               _map("images/map.png")
{
    _character.setPosition(_window.getWindowSize().x / 2, _window.getWindowSize().y / 2);
    _camera.setCenter(_character.x(), _character.y());

    _pixelsPerSecond = 400;
    _lastSecond = 0;
}

Game::~Game()
{
}

void Game::update()
{
    _window.update();

    float globTime = _globTime.asSeconds();

    if (int(globTime) > _lastSecond) // update 1 time per a second
    {
        _lastSecond = int(globTime);
        _character.update();
    }

    _textbox.clear();
    _textbox.setup(5, 16, 150, sf::Vector2f(_character.x() - _camera.getSize().x / 2, _character.y() - _camera.getSize().y / 2));
    _textbox.add("Health: " + std::to_string(_character.health()) + "%");
    _textbox.add("Hunger: " + std::to_string(_character.hunger()) + "%");
    _textbox.add("Cold: " + std::to_string(_character.cold()) + "%");

    _moveCharacter();
    interactionWithMap();
    _window.setView(_camera.view());
}

void Game::_moveCharacter()
{
    if (!_character.isAlive())
    {
        _textbox.clear();
        _textbox.setup(0, 25, 150, sf::Vector2f(_character.x() - 32, _character.y() - 32));
        _textbox.add("Game over");
        return;
    }

    if (_characterDirection != None)
    {
        float speed = _elapsed.asSeconds() * _pixelsPerSecond;
        _character.move(_characterDirection, speed);
        _camera.setCenter(_character.x(), _character.y());
    }
}

void Game::render()
{
    _window.clear();
    _map.render(_window.getRenderWindow());
    sf::Sprite sprite = _character.getSprite();
    _window.draw(sprite);
    _textbox.render(_window.getRenderWindow());
    _window.display();
}

sf::Time Game::getElapsed()
{
    return _elapsed;
}

void Game::restartClock()
{
    _elapsed = _clock.restart();
    _globTime += _elapsed;
}

Window *Game::getWindow()
{
    return &_window;
}

void Game::interactionWithMap()
{
    float x = _character.x();
    float y = _character.y();
    Direction direction = _character.direction();
    float h = 32; // height of character
    float w = 32; // width of character
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
            if (tileMap[i][j] == '0')
            {
                switch (direction)
                {
                case Up:
                    y = i * 32 + 32;
                    break;
                case Down:
                    y = i * 32 - h;
                    break;
                case Left:
                    x = j * 32 + 32;
                    break;
                case Right:
                    x = j * 32 - w;
                    break;
                default:
                    break;
                }
            }
        }
    _character.setPosition(x, y);
}

void Game::handleInput()
{
    _characterDirection = None;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _characterDirection = Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _characterDirection = Right;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _characterDirection = Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _characterDirection = Down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
    {
        _window.toggleFullscreen();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _window.~Window();
    }
}
