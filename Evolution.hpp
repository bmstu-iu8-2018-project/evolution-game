#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include <SFML/Window.hpp>
#include <thread>

#include "Keyboard.hpp"
#include "Map.hpp"
#include "Pixel.hpp"
#include "Button.hpp"

class Evolution
{
    //Button button1;
    //Button button2;
    Map map;
    sf::RenderWindow window;                   // std::shared_ptr<sf::RenderWindow> window; // может так?
    Keyboard keyboard;
    const unsigned int iteraition = 100;
public:
    Evolution();
    void run();
};

#endif