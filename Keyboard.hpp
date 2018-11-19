#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

//  #pragma once

#include <map>
#include <SFML/Graphics.hpp>

class Keyboard
{
    std::map<sf::Keyboard::Key, bool> keys;
public:
    void press(sf::Keyboard::Key key);
    void release(sf::Keyboard::Key key);
    bool isPressed(sf::Keyboard::Key key);
};

#endif
