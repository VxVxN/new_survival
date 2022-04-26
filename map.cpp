#include <SFML/Graphics.hpp>

class Map
{
public:
    Map(const std::string);
    ~Map();

    void render(sf::RenderWindow &);

private:
    const int _height = 25;
    const int _width = 40;

    sf::Sprite _sprite;
    sf::Texture _texture;
};

Map::Map(const std::string filename)
{
    sf::Image image;
    if (!image.loadFromFile(filename))
    {
        throw "Failed to load map from file";
    }
    _texture.loadFromImage(image);
    _sprite.setTexture(_texture);
}

Map::~Map()
{
}

sf::String tileMap[25] = {
    "0000000000000000000000000000000000000000",
    "0                                      0",
    "0   s                                  0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0000000000000000000000000000000000000000",
};

void Map::render(sf::RenderWindow &window)
{
    for (int i = 0; i < _height; i++)
        for (int j = 0; j < _width; j++)
        {
            if (tileMap[i][j] == ' ')
                _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            if (tileMap[i][j] == 's')
                _sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
            if ((tileMap[i][j] == '0'))
                _sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));

            _sprite.setPosition(j * 32, i * 32);

            window.draw(_sprite);
        }
}