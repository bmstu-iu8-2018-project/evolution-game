#include "Button.hpp"

Button::Button(const float x, const float y, const float rotation)
    :   X(x),
        Y(y),
        button(sf::CircleShape(20, 3))
{
    Color = sf::Color(169, 169, 169);
    button.setOutlineThickness(1);
    button.setFillColor(Color);
    button.setOutlineColor(sf::Color::Red);
    button.setRotation(rotation);
}

double Button::GetX()
{
    return X;
}

double Button::GetY()
{
    return Y;
}

sf::CircleShape Button::GetButton()
{
    return button;
}

sf::Color Button::GetColor()
{
    return Color;
}

void Button::SetColor(sf::Color newColor)
{
    Color = newColor;
}

void Button::SetX(double newX)
{
    X = newX;
}

void Button::SetY(double newY)
{
    Y = newY;
}

void Button::Print(sf::RenderWindow* window)
{
    button.setFillColor(Color);
    button.setPosition(X, Y);
    window->draw(button);
}