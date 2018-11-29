#include "Button.hpp"

Button::Button(const double& x, const double& y) : X(x), Y(y){
    Color = sf::Color(169, 169, 169);
    button.setOutlineThickness(1);
    button.setFillColor(Color);
    button.setOutlineColor(sf::Color::Red);
    // button.setRotation(180);
}

double Button::GetX() {
    return X;
}

double Button::GetY() {
    return Y;
}

sf::CircleShape Button::GetButton() {
    return button;
}

sf::Color Button::GetColor() {
    return Color;
}

void Button::SetColor(sf::Color newColor) {
    Color = newColor;
}

void Button::SetX(double newX) {
    X = newX;
}

void Button::SetY(double newY) {
    Y = newY;
}