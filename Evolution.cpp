#include "Evolution.hpp"

bool flag;

//  boost::recursive_mutex mutex;

Evolution::Evolution()
{
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

void Evolution::Statistics()
{
    double statisticsOfLifeIt = 0;
    for (size_t inner = 0; inner < map.GetStaticOrganisms().size(); ++inner)
    {
        statisticsOfLifeIt += map.GetStaticOrganisms()[inner]->GetNumberOfLifeIterations();
    }
    statisticsOfLifeIt /= map.GetStaticOrganisms().size();
    boost::filesystem::path path = boost::filesystem::current_path().parent_path();
    path += "/recordsNew";
    if(!boost::filesystem::exists(path))
        boost::filesystem::create_directory(path);
    std::string path_to_file = path.string() + "/Statistics";
    std::fstream fl(path_to_file, std::ios::app);
    fl << map.GetEvolutionNamber() << " " << statisticsOfLifeIt << std::endl;
    fl.close();
}


void Evolution::run()
{
    map.MultiplyPixels(20);
    sf::CircleShape button = sf::CircleShape(20, 3);
    button.setOutlineThickness(1);
    button.setFillColor(sf::Color(169, 169, 169));
    button.setOutlineColor(sf::Color::Red);
    sf::CircleShape button2 = sf::CircleShape(20, 3);
    button2.setOutlineThickness(1);
    button2.setFillColor(sf::Color(169, 169, 169));
    button2.setOutlineColor(sf::Color::Red);
    button2.setRotation(180);
    //  threads.emplace_back(std::thread(&Evolution::CatchingEvents, this/*, std::ref(*this)*/));
    while(window.isOpen())
    {
        //for(size_t inner = 0; inner < 100; ++inner)
        while(map.GetNumberOfAliveOrganisms() > 10)
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
                }  else if (keyboard.isPressed(sf::Keyboard::W)) {
                    map.IncreaseTimesToSleep(10);
                    button.setFillColor(sf::Color::Green);
                } else if (keyboard.isPressed(sf::Keyboard::E)) {
                    if (map.GetTimeToSleep() >= 10) {
                        map.DecreaseTimesToSleep(10);
                    }
                    button2.setFillColor(sf::Color::Green);
                }
                if (!(keyboard.isPressed(sf::Keyboard::W))) {
                    button.setFillColor(sf::Color(169, 169, 169));
                }
                if (!(keyboard.isPressed(sf::Keyboard::E))) {
                    if (map.GetTimeToSleep() > 0)
                        button2.setFillColor(sf::Color(169, 169, 169));
                }
                window.clear();
            }
            flag = (map.GetTimeToSleep() > 10);
            if (flag) {
                map.Print(&window);
                map.Update();
            } else {
                map.Update();
            }

            //  threads.emplace_back(&Map::Update, map);
            //  threads.emplace_back(&Map::Print, map);
            button.setPosition(0, 5);
            button2.setPosition(40, 70);
            window.draw(button);
            window.draw(button2);
            window.display();

        }
        map.SetStaticOrganisms(map.GetOrganisms());
        Statistics();
        map.IncreaseEvolutionNumber();
        map.RecreateMap(map.GetStaticOrganisms());
    }
}