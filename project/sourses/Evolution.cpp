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
    path += "/records";
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
    int evNum = 1;
    while(window.isOpen())
    {
        window.clear();
        sf::Font font;
        font.loadFromFile("/home/mariasolovyova/CLionProjects/EvVv/Arial.ttf");

        sf::Text textEvolution("", font, 70);
        textEvolution.setColor(sf::Color::Green);
        textEvolution.setString("Evolution game");
        textEvolution.setStyle(sf::Text::Bold | sf::Text::Underlined);
        textEvolution.setPosition(600, 200);

        sf::Text Run("", font, 25);
        Run.setColor(sf::Color::Green);
        Run.setString("Run with :");
        Run.setStyle(sf::Text::Underlined);
        Run.setPosition(600, 500);

        sf::Text menu_newEvolution("", font, 25);
        menu_newEvolution.setColor(sf::Color::Red);
        menu_newEvolution.setString("New evolution");
        menu_newEvolution.setStyle(sf::Text::Underlined);
        menu_newEvolution.setPosition(800, 500);

        sf::Text setScale("", font, 25);
        setScale.setColor(sf::Color::Red);
        setScale.setString("Set scale:");
        setScale.setStyle(sf::Text::Underlined);
        setScale.setPosition(600, 400);

        sf::Text setWidth("", font, 25);
        setWidth.setColor(sf::Color::Green);
        setWidth.setString("Width: ");
        setWidth.setPosition(800, 400);

        sf::Text Width("", font, 25);
        Width.setColor(sf::Color::Green);
        Width.setString(std::to_string(width));
        Width.setPosition(925, 400);

        sf::Text setHeight("", font, 25);
        setHeight.setColor(sf::Color::Green);
        setHeight.setString("Height: ");
        setHeight.setPosition(800, 450);

        sf::Text Height("", font, 25);
        Height.setColor(sf::Color::Green);
        Height.setString(std::to_string(height));
        Height.setPosition(925, 450);

        sf::CircleShape increaseWidth(20, 4);
        increaseWidth.setFillColor(sf::Color(169, 169, 169));
        increaseWidth.setOutlineThickness(1);
        increaseWidth.setOutlineColor(sf::Color::Red);
        increaseWidth.setRotation(45);
        increaseWidth.setPosition(900, 390);
        sf::Text increase1("", font, 25);
        increase1.setColor(sf::Color::Red);
        increase1.setString("+");
        increase1.setPosition(893, 400);

        sf::CircleShape decreaseWidth(20, 4);
        decreaseWidth.setFillColor(sf::Color(169, 169, 169));
        decreaseWidth.setOutlineThickness(1);
        decreaseWidth.setOutlineColor(sf::Color::Red);
        decreaseWidth.setRotation(45);
        decreaseWidth.setPosition(980, 390);
        sf::Text decrease1("", font, 25);
        decrease1.setColor(sf::Color::Red);
        decrease1.setString("-");
        decrease1.setPosition(975, 400);

        sf::CircleShape increaseHeight(20, 4);
        increaseHeight.setFillColor(sf::Color(169, 169, 169));
        increaseHeight.setOutlineThickness(1);
        increaseHeight.setOutlineColor(sf::Color::Red);
        increaseHeight.setRotation(45);
        increaseHeight.setPosition(900, 440);
        sf::Text increase2("", font, 25);
        increase2.setColor(sf::Color::Red);
        increase2.setString("+");
        increase2.setPosition(893, 450);

        sf::CircleShape decreaseHeight(20, 4);
        decreaseHeight.setFillColor(sf::Color(169, 169, 169));
        decreaseHeight.setOutlineThickness(1);
        decreaseHeight.setOutlineColor(sf::Color::Red);
        decreaseHeight.setRotation(45);
        decreaseHeight.setPosition(980, 440);
        sf::Text decrease2("", font, 25);
        decrease2.setColor(sf::Color::Red);
        decrease2.setString("-");
        decrease2.setPosition(975, 450);

        sf::CircleShape increaseEv(20, 4);
        increaseEv.setFillColor(sf::Color(169, 169, 169));
        increaseEv.setOutlineThickness(1);
        increaseEv.setOutlineColor(sf::Color::Red);
        increaseEv.setRotation(45);
        increaseEv.setPosition(820, 540);
        sf::Text increaseNumEv("", font, 25);
        increaseNumEv.setColor(sf::Color::Red);
        increaseNumEv.setString("+");
        increaseNumEv.setPosition(813, 550);

        sf::CircleShape decreaseEv(20, 4);
        decreaseEv.setFillColor(sf::Color(169, 169, 169));
        decreaseEv.setOutlineThickness(1);
        decreaseEv.setOutlineColor(sf::Color::Red);
        decreaseEv.setRotation(45);
        decreaseEv.setPosition(900, 540);
        sf::Text decreaseNumEv("", font, 25);
        decreaseNumEv.setColor(sf::Color::Red);
        decreaseNumEv.setString("-");
        decreaseNumEv.setPosition(895, 550);

        sf::Text runEv("", font, 25);
        runEv.setColor(sf::Color::Red);
        runEv.setString("Run");
        runEv.setStyle(sf::Text::Underlined);
        runEv.setPosition(950, 550);

        sf::Text numberEV("", font, 25);
        numberEV.setColor(sf::Color::Green);
        numberEV.setString(std::to_string(evNum));
        numberEV.setPosition(850, 550);

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
            {
                if (width < 94)
                {
                    ++width;
                }
                increaseWidth.setFillColor(sf::Color::Green);
            }
            else if (keyboard.isPressed(sf::Keyboard::H))
            {
                if (height < 60)
                {
                    ++height;
                }
                increaseHeight.setFillColor(sf::Color::Green);
            }
            else if (keyboard.isPressed(sf::Keyboard::E))
            {
                if (width >= 10)
                {
                    --width;
                }
                decreaseWidth.setFillColor(sf::Color::Green);
            }
            else if (keyboard.isPressed(sf::Keyboard::J))
            {
                if (height >= 10)
                {
                    --height;
                }
                decreaseHeight.setFillColor(sf::Color::Green);
            }
            else if (keyboard.isPressed(sf::Keyboard::U))
            {
                if (evNum == 1)
                    evNum += 9;
                else
                    evNum += 10;
                increaseEv.setFillColor(sf::Color::Green);
            }
            else if (keyboard.isPressed(sf::Keyboard::D))
            {
                if (evNum > 10)
                    evNum -= 10;
                else if (evNum == 10)
                    evNum -= 9;
                decreaseEv.setFillColor(sf::Color::Green);
            }
            if (!(keyboard.isPressed(sf::Keyboard::W)))
            {
                increaseWidth.setFillColor(sf::Color(169, 169, 169));
            }
            if (!(keyboard.isPressed(sf::Keyboard::E)))
            {
                decreaseWidth.setFillColor(sf::Color(169, 169, 169));
            }
            if (!(keyboard.isPressed(sf::Keyboard::H)))
            {
                increaseHeight.setFillColor(sf::Color(169, 169, 169));
            }
            if (!(keyboard.isPressed(sf::Keyboard::J)))
            {
                decreaseHeight.setFillColor(sf::Color(169, 169, 169));
            }
            window.clear();
        }

        int menuNum = 0;

        if (sf::IntRect(800, 500, 180, 50).contains(sf::Mouse::getPosition(window))) {
            menu_newEvolution.setColor(sf::Color::White);
            menuNum = 1;
        } else if (sf::IntRect(950, 550, 100, 50).contains(sf::Mouse::getPosition(window))) {
            runEv.setColor(sf::Color::White);
            menuNum = 2;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) {
                menu_newEvolution.setStyle(sf::Text::Bold | sf::Text::Underlined);
                map = Map(width, height);
                run();
            } else if (menuNum == 2) {
                runEv.setStyle(sf::Text::Bold | sf::Text::Underlined);
                map.UploadFromFile(evNum, width, height);
                run();
            }
        }

        window.draw(textEvolution);
        window.draw(menu_newEvolution);
        window.draw(Run);
        window.draw(setScale);
        window.draw(setHeight);
        window.draw(setWidth);
        window.draw(Height);
        window.draw(Width);
        window.draw(increaseHeight);
        window.draw(increase2);
        window.draw(increaseWidth);
        window.draw(increase1);
        window.draw(decreaseHeight);
        window.draw(decrease2);
        window.draw(decreaseWidth);
        window.draw(decrease1);
        window.draw(increaseEv);
        window.draw(increaseNumEv);
        window.draw(decreaseEv);
        window.draw(decreaseNumEv);
        window.draw(runEv);
        window.draw(numberEV);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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