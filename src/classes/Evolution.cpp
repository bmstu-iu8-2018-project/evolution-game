#include "Evolution.hpp"


Evolution::Evolution()
{
    map = Map();
    window.create(sf::VideoMode(map.GetWidth(), map.GetHeight()), "Evolution");
}

void Evolution::run()
{
    map.MultiplyPixels(5);
    map.CreateFood(150);
    map.SetPoison(15);
    while (window.isOpen())
    {
        for (unsigned int inner  = 0; inner < iteraition; ++inner)
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
                else if (keyboard.isPressed(sf::Keyboard::S))
                {
                    map.SaveToFile();
                    window.close();
                }
                else if (keyboard.isPressed(sf::Keyboard::U))
                {
                    map.UploadFromFile();
                    window.close();
                }
                window.clear();
            }
            for (size_t i = 1; i < map.GetHeightInCells(); ++i)
            {
                for (size_t j = 0; j < map.GetWidthInCells(); ++j)
                {
                    map[i][j]->SetHex().setPosition((float) map[i][j]->GetX(), (float) map[i][j]->GetY());
                    window.draw(map[i][j]->GetHex());
                }
            }
            map.Update();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            window.display();
        }
        /*std::vector<Hexagon*> organisms = map.GetOrganisms();
        size_t size = organisms.size();
        for (size_t i = 0; i < size; ++i)
        {
                for (int j = 0; j < 5; ++j)
                {
                    organisms.push_back(organisms[i]);
                }
        }
        for (size_t i = 0; i < size; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                Brain brain = organismsNew[i]->GetBrain();
                brain.Train();
                organismsNew[i]->SetBrain(brain);
                organisms.push_back(organismsNew[i]);
            }
        }*/
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}