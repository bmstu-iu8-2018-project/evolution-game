#include "Evolution.hpp"


Evolution::Evolution()
{
    map = Map(94, 60);
    window.create(sf::VideoMode(map.GetWidth(), map.GetHeight()), "Evolution");
    buttonDecrease= Button(0, 5, 0);
    buttonIncrease = Button(40, 70, 180);
}

Evolution::Evolution(const Evolution& ev)
        :        map(ev.map),
                 keyboard(ev.keyboard)
{
    window.create(sf::VideoMode(ev.map.GetWidth(), ev.map.GetHeight()), "Evolution");
}

Evolution::Evolution(Evolution&& ev)
        :    map(std::move(ev.map)),
             keyboard(std::move(ev.keyboard))
{
    window.create(sf::VideoMode(ev.map.GetWidth(), ev.map.GetHeight()), "Evolution");
}

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
    fl << map.GetEvolutionNumber() << " " << statisticsOfLifeIt << std::endl;
    fl.close();
}

void Evolution::Menu()
{
    size_t width = 94;
    size_t height = 60;
    while(window.isOpen())
    {
        window.clear();
        sf::Font font;
        font.loadFromFile("resourses/Arial.ttf");

        sf::Text textEvolution("", font, 70);
        textEvolution.setColor(sf::Color::Green);
        textEvolution.setString("Evolution game");
        textEvolution.setStyle(sf::Text::Bold | sf::Text::Underlined);
        textEvolution.setPosition(600, 200);

        sf::Text Run("", font, 25);
        Run.setColor(sf::Color::Green);
        Run.setString("Run with :");
        Run.setStyle(sf::Text::Underlined);
        Run.setPosition(600, 400);

        sf::Text menu_newEvolution("", font, 25);
        menu_newEvolution.setColor(sf::Color::Red);
        menu_newEvolution.setString("New evolution");
        menu_newEvolution.setStyle(sf::Text::Underlined);
        menu_newEvolution.setPosition(800, 400);

        sf::Text setScale("", font, 25);
        setScale.setColor(sf::Color::Red);
        setScale.setString("Set scale:");
        setScale.setStyle(sf::Text::Underlined);
        setScale.setPosition(800, 600);
        sf::Text setWidth("", font, 25);
        setWidth.setColor(sf::Color::Green);
        setWidth.setString("Width: " + std::to_string(width));
        setWidth.setPosition(950, 600);
        sf::Text setHeight("", font, 25);
        setHeight.setColor(sf::Color::Green);
        setHeight.setString("Height: " + std::to_string(height));
        setHeight.setPosition(950, 650);

        sf::Text menu_100_generation("", font, 25);
        menu_100_generation.setColor(sf::Color::Red);
        menu_100_generation.setString("100 generation");
        menu_100_generation.setStyle(sf::Text::Underlined);
        menu_100_generation.setPosition(800, 450);

        sf::Text menu_1000_generation("", font, 25);
        menu_1000_generation.setColor(sf::Color::Red);
        menu_1000_generation.setString("1000 generation");
        menu_1000_generation.setStyle(sf::Text::Underlined);
        menu_1000_generation.setPosition(800, 500);

        sf::Text menu_5000_generation("", font, 25);
        menu_5000_generation.setColor(sf::Color::Red);
        menu_5000_generation.setString("5000 generation");
        menu_5000_generation.setStyle(sf::Text::Underlined);
        menu_5000_generation.setPosition(800, 550);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || keyboard.isPressed(sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                keyboard.press(event.key.code);
            else if (event.type == sf::Event::KeyReleased)
                keyboard.release(event.key.code);
            else if (keyboard.isPressed(sf::Keyboard::W))
                width -= 5;
            else if (keyboard.isPressed(sf::Keyboard::H))
                height -= 5;
            window.clear();
        }

        int menuNum = 0;

        if (sf::IntRect(800, 400, 180, 50).contains(sf::Mouse::getPosition(window))) {
            menu_newEvolution.setColor(sf::Color::White);
            menuNum = 1;
        } else if (sf::IntRect(800, 450, 180, 50).contains(sf::Mouse::getPosition(window))) {
            menu_100_generation.setColor(sf::Color::White);
            menuNum = 2;
        } else if (sf::IntRect(800, 500, 180, 50).contains(sf::Mouse::getPosition(window))) {
            menu_1000_generation.setColor(sf::Color::White);
            menuNum = 3;
        } else if (sf::IntRect(800, 550, 180, 50).contains(sf::Mouse::getPosition(window))) {
            menu_5000_generation.setColor(sf::Color::White);
            menuNum = 4;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) {
                menu_newEvolution.setStyle(sf::Text::Bold | sf::Text::Underlined);
                map = Map(width, height);
                run();
            } else if (menuNum == 2) {
                menu_100_generation.setStyle(sf::Text::Bold | sf::Text::Underlined);
                map.UploadFromFile(100);
                run();
            } else if (menuNum == 3) {
                menu_1000_generation.setStyle(sf::Text::Bold | sf::Text::Underlined);
                map.UploadFromFile(1000);
                run();
            } else if (menuNum == 4) {
                menu_5000_generation.setStyle(sf::Text::Bold | sf::Text::Underlined);
                map.UploadFromFile(5000);
                run();
            }
        }

        window.draw(textEvolution);
        window.draw(menu_newEvolution);
        window.draw(menu_100_generation);
        window.draw(menu_1000_generation);
        window.draw(menu_5000_generation);
        window.draw(Run);
        window.draw(setScale);
        window.draw(setHeight);
        window.draw(setWidth);

        window.display();
    }
}


void Evolution::run()
{
    map.MultiplyPixels(10);
    while (window.isOpen())
    {
        if (map.GetEvolutionNumber() == 1 || map.GetEvolutionNumber() % 10 == 0)
            map.SaveToFile();
        while (map.GetNumberOfAliveOrganisms() > 0 && window.isOpen())
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
                }
                else if (keyboard.isPressed(sf::Keyboard::U))
                {
                    map.UploadFromFile(1570);
                }
                else if (keyboard.isPressed(sf::Keyboard::W))
                {
                    map.IncreaseTimesToSleep(10);
                    buttonIncrease.SetColor(sf::Color::Green);
                    buttonIncrease.Print(&window);
                }
                else if (keyboard.isPressed(sf::Keyboard::E))
                {
                    if (map.GetTimeToSleep() >= 10)
                    {
                        map.DecreaseTimesToSleep(10);
                    }
                    buttonDecrease.SetColor(sf::Color::Green);
                    buttonDecrease.Print(&window);
                }
                if (!(keyboard.isPressed(sf::Keyboard::W)))
                {
                    buttonIncrease.SetColor(sf::Color(169, 169, 169));
                    buttonIncrease.Print(&window);
                }
                if (!(keyboard.isPressed(sf::Keyboard::E)))
                {
                    if (map.GetTimeToSleep() > 0)
                        buttonDecrease.SetColor(sf::Color(169, 169, 169));
                    buttonDecrease.Print(&window);
                }
                window.clear();
            }
            PrintOrNot = (map.GetTimeToSleep() > 5);
            if (PrintOrNot)
                map.Print(&window);
            map.Update();
            buttonIncrease.Print(&window);
            buttonDecrease.Print(&window);

            window.display();
        }
        Statistics();
        map.IncreaseEvolutionNumber();
        map.RecreateMap(map.GetStaticOrganisms());
    }
}