#include "Evolution.hpp"


Evolution::Evolution()
{
    map = Map();
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

        for (size_t i = 1; i < map.GetHeightInCells(); ++i)
        {
            for (size_t j = 0; j < map.GetWidthInCells(); ++j)
            {
                map[i][j].GetHex().setPosition((float)map[i][j].GetX(), (float)map[i][j].GetY());
                window.draw(map[i][j].GetHex());
            }
        }

        //map.Update();
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
