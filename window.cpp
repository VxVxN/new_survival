#include <iostream>
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window();
    Window(const std::string &title, const sf::Vector2u &size);
    ~Window();

    void clear();
    void display();

    void update();

    bool isDone();
    bool isFullscreen();
    sf::Vector2u getWindowSize();
    sf::RenderWindow &getRenderWindow();

    void toggleFullscreen();
    void setView(sf::View);

    void draw(sf::Drawable &drawable);

    const sf::Vector2u &getSize();

private:
    void _setup(const std::string &title, const sf::Vector2u &size);
    void _destroy();
    void _create();

    sf::RenderWindow _window;
    sf::Vector2u _windowSize;
    std::string _windowTitle;
    bool _isDone;
    bool _isFullscreen;
};

Window::Window()
{
    _setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string &title, const sf::Vector2u &size)
{
    _setup(title, size);
}

Window::~Window()
{
    _isDone = true;
    _destroy();
}

void Window::_setup(const std::string &title, const sf::Vector2u &size)
{
    _windowTitle = title;
    _windowSize = size;
    _isFullscreen = false;
    _isDone = false;
    _create();
}

void Window::_create()
{
    auto style = (_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    _window.create({_windowSize.x, _windowSize.y, 32}, _windowTitle, style);
}

void Window::_destroy()
{
    _window.close();
}

void Window::update()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _isDone = true;
        }
    }
}

void Window::toggleFullscreen()
{
    _isFullscreen = !isFullscreen();
    _destroy();
    _create();
}

void Window::clear()
{
    _window.clear(sf::Color::Black);
}

void Window::display()
{
    _window.display();
}

bool Window::isDone()
{
    return _isDone;
}

bool Window::isFullscreen()
{
    return _isFullscreen;
}

sf::Vector2u Window::getWindowSize()
{
    return _windowSize;
}

void Window::draw(sf::Drawable &drawable)
{
    _window.draw(drawable);
}

sf::RenderWindow &Window::getRenderWindow()
{
    return _window;
}

void Window::setView(sf::View view)
{
    _window.setView(view);
}
