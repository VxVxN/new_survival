#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.cpp"

int main()
{
    Game game;
    while (!game.getWindow()->isDone())
    {
        game.update();
        game.render();
        game.restartClock();
    }
    return EXIT_SUCCESS;
}