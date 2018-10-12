#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 1000), "SFML works!");
    Map map(&window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (size_t i = 0; i < map.Size(); ++i) {
            map[i].hexagon.setPosition(map[i].X, map[i].Y);
            window.draw(map[i].hexagon);
        }
        window.display();
    }

    return 0;
}

