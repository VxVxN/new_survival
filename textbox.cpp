#include <SFML/Graphics.hpp>
#include <iostream>

class Textbox
{
public:
    Textbox();
    Textbox(int visible, int charSize,
            int width, sf::Vector2f screenPos);
    ~Textbox();
    void setup(int visible, int charSize,
               int width, sf::Vector2f screenPos);
    void add(std::string message);
    void clear();
    void render(sf::RenderWindow &wind);

private:
    std::vector<std::string> _messages;
    int _numVisible;
    sf::RectangleShape _backdrop;
    sf::Font _font;
    sf::Text _content;
};

Textbox::Textbox()
{
    setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int charSize,
                 int width, sf::Vector2f screenPos)
{
    setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox()
{
    clear();
}

void Textbox::setup(int visible, int charSize,
                    int width, sf::Vector2f screenPos)
{
    _numVisible = visible;
    sf::Vector2f l_offset(2.0f, 2.0f);
    _font.loadFromFile("arial.ttf");
    _content.setFont(_font);
    _content.setString("");
    _content.setCharacterSize(charSize);
    _content.setFillColor(sf::Color::White);
    _content.setPosition(screenPos + l_offset);
    _backdrop.setSize(sf::Vector2f(width, (visible * (charSize * 1.2f))));
    _backdrop.setFillColor(sf::Color(90, 90, 90, 90));
    _backdrop.setPosition(screenPos);
}

void Textbox::add(std::string l_message)
{
    _messages.push_back(l_message);
    if (_messages.size() < 6)
    {
        return;
    }
    _messages.erase(_messages.begin());
}

void Textbox::clear()
{
    _messages.clear();
}

void Textbox::render(sf::RenderWindow &wind)
{
    std::string content;
    for (auto &itr : _messages)
    {
        content.append(itr + "\n");
    }
    if (content != "")
    {
        _content.setString(content);
        wind.draw(_backdrop);
        wind.draw(_content);
    }
}