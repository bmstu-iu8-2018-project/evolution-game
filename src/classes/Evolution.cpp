#include "Evolution.hpp"
#include "StationaryObject.hpp"


Evolution::Evolution()
{
    window.create(sf::VideoMode(width, height), "Evolution");
    map = Map(window);
}
size_t Evolution::getWidth()
{
    return width;
}

size_t Evolution::getHeight()
{
    return height;
}

void Evolution::run()
{
    StationaryObject hexagonObj;
    //  hexagonObj.setPosition(map);
    std::vector<StationaryObject> vecObj;
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
            for (size_t i = 0; i < map.Size(); ++i)
            {
                map[i].hexagon.setPosition(map[i].X, map[i].Y);
                window.draw(map[i].hexagon);
            }
            for (size_t i = 0; i < vecObj.size(); ++i) {
                window.draw(vecObj[i].getObject());
            }
            //hexagonObj.getObject().setPosition(hexagonObj.getPosX(), hexagonObj.getPosY());
            //hexagonObj.setPos(map);
            window.draw(hexagonObj.getObject());
            window.display();
        }
    }
}