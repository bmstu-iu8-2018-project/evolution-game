#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include <SFML/Window.hpp>
#include <thread>

#include "Keyboard.hpp"
#include "Map.hpp"
#include "Pixel.hpp"

class Evolution
{
    Map map;
    sf::RenderWindow window;                   // std::shared_ptr<sf::RenderWindow> window; // может так?
    Keyboard keyboard;
    unsigned int evolutionNumber;
    std::vector<std::thread> threads;
public:
    Evolution();
    Evolution(const Evolution&);
    Evolution(Evolution&&);
    void run();
    void CatchingEvents();
};

#endif