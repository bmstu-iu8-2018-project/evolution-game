#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Keyboard.hpp"


class Evolution
{
    Map map;
    // std::vector для пикселят
    // std::shared_ptr<sf::RenderWindow> window; // может так?
    sf::RenderWindow window;
    Keyboard keyboard;
    static const std::size_t width = 2000;
    static const std::size_t height = 1000;
public:
    Evolution();
    void run();
    static size_t getWidth();
    static size_t getHeight();
};

#endif