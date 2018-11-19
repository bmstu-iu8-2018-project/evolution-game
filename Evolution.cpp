#include "Evolution.hpp"

Evolution::Evolution()
{
    map = Map();
    //button1 = Button(0, 0);
    window.create(sf::VideoMode(map.GetWidth(), map.GetHeight()), "Evolution");
}

void Evolution::run()
{
    int x = 100;
    map.MultiplyPixels(5);
    map.CreateFood(150);
    map.SetPoison(15);
    sf::CircleShape button = sf::CircleShape(20, 3);
    button.setOutlineThickness(1);
    button.setFillColor(sf::Color(169, 169, 169));
    button.setOutlineColor(sf::Color::Red);
    sf::CircleShape button2 = sf::CircleShape(20, 3);
    button2.setOutlineThickness(1);
    button2.setFillColor(sf::Color(169, 169, 169));
    button2.setOutlineColor(sf::Color::Red);
    button2.setRotation(180);
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
                    // map.UploadFromFile();
                    window.close();
                } else if (keyboard.isPressed(sf::Keyboard::W)) {
                    x += 100;
                    button.setFillColor(sf::Color::Green);
                } else if (keyboard.isPressed(sf::Keyboard::E)) {
                    if (x >= 100)
                        x -= 100;
                    button2.setFillColor(sf::Color::Green);
                }
                if (!(keyboard.isPressed(sf::Keyboard::W))) {
                    button.setFillColor(sf::Color(169, 169, 169));
                }
                if (!(keyboard.isPressed(sf::Keyboard::E))) {
                    if (x > 0)
                        button2.setFillColor(sf::Color(169, 169, 169));
                }
                window.clear();
            }
            for (size_t i = 1; i < map.GetHeightInCells(); ++i)
            {
                for (size_t j = 0; j < map.GetWidthInCells(); ++j)
                {
                    map[i][j]->Print(&window);
                    if (map[i][j]->GetHex().getFillColor() == sf::Color::Black)
                        throw std::runtime_error("not hex");

                }
            }
            map.Update();
            /*button1.SetX(20);
            button1.SetY(5);
            button1.GetButton().setPosition(50, 5);
            window.draw(button1.GetButton());*/
            button.setPosition(0, 5);
            button2.setPosition(40, 70);
            window.draw(button);
            window.draw(button2);
            std::this_thread::sleep_for(std::chrono::milliseconds(x));
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