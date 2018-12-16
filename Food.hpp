#ifndef FOOD_HPP
#define FOOD_HPP

#include "Hexagon.hpp"

#include </home/anastasia/CLionProjects/evolution/tools/json-develop/single_include/nlohmann/json.hpp>

using Json = nlohmann::json;

class Food
        : public Hexagon
{
public:
    Food(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, double Medicine = rand() % 5)
        :    Hexagon(Type::FOOD, xNew, yNew, CellStrNew, CellColNew)
    {
        medicine = Medicine;
        lifes = 40;
    }

    void Print(sf::RenderWindow* window) const override
    {
        sf::CircleShape hexagon1(10, 6);
        hexagon1.setFillColor(sf::Color(93, 161, 48));
        hexagon1.setOutlineThickness(1);
        hexagon1.setOutlineColor(sf::Color::Black);
        hexagon1.setPosition(x, y);
        window->draw(hexagon1);
    }
};

class Water
        : public Hexagon
{
public:
    Water(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
            :    Hexagon(Type::WATER, xNew, yNew, CellStrNew, CellColNew)
    {
        medicine = 0;
    }

    void Print(sf::RenderWindow* window) const override
    {
        sf::CircleShape hexagon1(10, 6);
        hexagon1.setFillColor(sf::Color(66, 170, 255));
        hexagon1.setOutlineThickness(1);
        hexagon1.setOutlineColor(sf::Color::Black);
        hexagon1.setPosition(x, y);
        window->draw(hexagon1);
    }
};

class Poison
        : public Hexagon
{
public:
    Poison(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, double Medicine = -(rand() % 12))
            :    Hexagon(Type::POISON, xNew, yNew, CellStrNew, CellColNew)
    {
        medicine = Medicine;
    }
    ~Poison() = default;

    void Print(sf::RenderWindow* window) const override
    {
        sf::CircleShape hexagon1(10, 6);
        hexagon1.setFillColor(sf::Color(207, 66, 52));
        hexagon1.setOutlineThickness(1);
        hexagon1.setOutlineColor(sf::Color::Black);
        hexagon1.setPosition(x, y);
        window->draw(hexagon1);
    }
};

class Wall
        : public Hexagon
{
public:
    Wall()
            :    Hexagon(Type::WALL, 0, 0, 0, 0)
    {
        medicine = 0;
        lifes = 0;
    }

};

#endif