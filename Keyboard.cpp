#include "Keyboard.hpp"

void Keyboard::press(sf::Keyboard::Key key)
{
    this->keys[key] = true;
}

void Keyboard::release(sf::Keyboard::Key key)
{
    this->keys[key] = false;
}

bool Keyboard::isPressed(sf::Keyboard::Key key)
{

    auto it = keys.find(key);
    if (it != keys.end())
    {
        return it->second;
    }
    return false;
}
