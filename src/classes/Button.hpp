
#ifndef EVOLUTION_BUTTON_H
#define EVOLUTION_BUTTON_H


#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>

class Button {
public:
    Button() = default;
    ~Button() = default;
    Button(const double& x, const double& y);

    double GetX();
    double GetY();
    sf::Color GetColor();

    sf::CircleShape GetButton();

    void SetColor(sf::Color newColor);
    void SetX(double newX);
    void SetY(double newY);

private:
    sf::CircleShape button = sf::CircleShape(20, 3);
    double X;
    double Y;
    sf::Color Color;
    float Rotation;
};


#endif //EVOLUTION_BUTTON_H
