#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include <thread>

#include <SFML/Window.hpp>

#include "Keyboard.hpp"
#include "Map.hpp"
#include "Pixel.hpp"
#include "Button.hpp"

class Evolution
{
    Map map;
    sf::RenderWindow window;
    Keyboard keyboard;
    Button buttonIncrease;
    Button buttonDecrease;
    bool PrintOrNot;
public:
    Evolution();
    Evolution(const Evolution&);
    Evolution(Evolution&&);
    void run();
    void Statistics();
    void Menu();
};

#endif