#include "window.cpp"
#include "character.cpp"
#include "map.cpp"
#include "camera.cpp"

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
    void interactionWithMap();

    Window _window;
    Character _character;
    Map _map;
    Camera _camera;

    sf::Clock _clock;
    sf::Time _elapsed;
    float _pixelsPerSecond;
};

Game::Game() : _window("Survival", sf::Vector2u(1600, 1000)),
               _character("images/characters.png"),
               _map("images/map.png")
{
    _character.setPosition(_window.getWindowSize().x / 2, _window.getWindowSize().y / 2);
    _camera.setCenter(_character.x(), _character.y());

    _pixelsPerSecond = 400;
}

Game::~Game()
{
}

void Game::update()
{
    _window.update();
    _moveCharacter();
    interactionWithMap();
    _window.setView(_camera.view());
}

void Game::_moveCharacter()
{
    float speed = _elapsed.asSeconds() * _pixelsPerSecond;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _character.move(Left, speed);
        _camera.setCenter(_character.x(), _character.y());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _character.move(Right, speed);
        _camera.setCenter(_character.x(), _character.y());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _character.move(Up, speed);
        _camera.setCenter(_character.x(), _character.y());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _character.move(Down, speed);
        _camera.setCenter(_character.x(), _character.y());
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