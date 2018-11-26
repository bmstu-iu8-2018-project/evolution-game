#include "Evolution.hpp"

//  boost::recursive_mutex mutex;

Evolution::Evolution()
{
    evolutionNumber = 1;
    map = Map();
    window.create(sf::VideoMode(map.GetWidth(), map.GetHeight()), "Evolution");
}

Evolution::Evolution(const Evolution& ev)
    :        map(ev.map),
             keyboard(ev.keyboard)
{
    window.create(sf::VideoMode(ev.map.GetWidth(), ev.map.GetHeight()), "Evolution");
}

Evolution::Evolution(Evolution&& ev)
    :    threads(std::move(ev.threads)),
         map(std::move(ev.map)),
         keyboard(std::move(ev.keyboard))
{
     window.create(sf::VideoMode(ev.map.GetWidth(), ev.map.GetHeight()), "Evolution");
}

/*void Evolution::CatchingEvents()
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
            else if (keyboard.isPressed(sf::Keyboard::S))
            {
                map.SaveToFile();
                //  window.close();
            }
            else if (keyboard.isPressed(sf::Keyboard::U))
            {
                map.UploadFromFile();
            }
            window.clear();
        }
    }
}*/


void Evolution::run()
{
    map.MultiplyPixels(10);
    //  threads.emplace_back(std::thread(&Evolution::CatchingEvents, this/*, std::ref(*this)*/));
    while(window.isOpen())
    {
        for(size_t inner = 0; inner < 100; ++inner)
        //while(map.GetNumberOfAliveOrganisms() > 0)
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
                    //  window.close();
                }
                else if (keyboard.isPressed(sf::Keyboard::U))
                {
                    map.UploadFromFile();
                }
                window.clear();
            }
            map.Print(&window);
            map.Update();
            //  threads.emplace_back(&Map::Update, map);
            //  threads.emplace_back(&Map::Print, map);
            window.display();
        }
        ++evolutionNumber;
        //std::vector<Hexagon*> organisms = map.GetOrganisms();
        // вызов статистики
        std::vector<Hexagon*> newOrganisms = map.GetOrganisms();
        size_t size = newOrganisms.size();
        for (size_t i = 0; i < size; ++i)
        {
            //for (int j = 0; j < 5; ++j)
            //{
               //Brain brain = newOrganisms[i]->GetBrain();
               //brain.Train();
               // newOrganisms[i]->SetBrain(brain);
                newOrganisms[i]->SetLifes(99);
                newOrganisms[i]->ResetNumberOfLifeIterations();
                newOrganisms[i]->ResetMedicine();
                //  organisms.push_back(newOrganisms[i]);
            //}
        }
        map.RecreateMap(newOrganisms);
    }
}