#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include <SFML/Window.hpp>
#include <thread>

#include "Keyboard.hpp"
#include "Map.hpp"

class Evolution
{
    Map map;
    sf::RenderWindow window;                   // std::shared_ptr<sf::RenderWindow> window; // может так?
    Keyboard keyboard;
public:
    Evolution();
    void run();
};

#endif