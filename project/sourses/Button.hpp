#ifndef BUTTON_H
#define BUTTON_H

#include <cmath>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Button
{
public:
    Button() = default;
    ~Button() = default;
    Button(const float, const float, const float);

    double GetX();
    double GetY();
    sf::Color GetColor();

    sf::CircleShape GetButton();

    void SetColor(sf::Color newColor);
    void SetX(double newX);
    void SetY(double newY);

    void Print(sf::RenderWindow* window);

private:
    sf::CircleShape button;
    float X;
    float Y;
    sf::Color Color;
    float Rotation;
};


#endif
