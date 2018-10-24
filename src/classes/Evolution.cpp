#include "Evolution.hpp"


Evolution::Evolution()
{
    map = Map();
    sunMap = SunMap();
    window.create(sf::VideoMode(2000, 1000), "Evolution");
}

void Evolution::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || keyboard.isPressed(sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                keyboard.press(event.key.code);
            else if (event.type == sf::Event::KeyReleased)
                keyboard.release(event.key.code);
            window.clear();
        }

        for (size_t i = 1; i < map.getHeightInCells(); ++i)
        {
            for (size_t j = 0; j < map.getWidthInCells(); ++j)
            {
                map[i][j].getHex().setPosition(map[i][j].getX(), map[i][j].getY());
                window.draw(map[i][j].getHex());
                map[i][j].Update(map, sunMap);
            }
        }
        for (size_t j = 0; j < sunMap.getWidthInCells(); ++j)
        {
            sunMap.getGrafics()[j].hexagon.setPosition(sunMap.getGrafics()[j].X, sunMap.getGrafics()[j].Y);
            window.draw(sunMap.getGrafics()[j].hexagon);
        }
        sunMap.Update(&window);
        window.display();
        //  std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
