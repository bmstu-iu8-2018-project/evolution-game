#ifndef EVOLUTION_FOOD_HPP
#define EVOLUTION_FOOD_HPP

#include "Hexagon.hpp"

class Food
        : public Hexagon
{
public:
    Food(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
        :    Hexagon(Type::FOOD, xNew, yNew, CellStrNew, CellColNew)
    {
        hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
        medicine = rand() % 5;
    }
    void Update(Map& map)
    {}
    ~Food() override = default;
};

class Water
        : public Hexagon
{
public:
    Water(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
            :    Hexagon(Type::WATER, xNew, yNew, CellStrNew, CellColNew)
    {
        hexagon.setFillColor(sf::Color(66, 170, 255)); // Blue
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
        medicine = 0;
    }
    void Update(Map& map)
    {}
    ~Water() override = default;
};

class Poison
        : public Hexagon
{
public:
    Poison(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
            :    Hexagon(Type::POISON, xNew, yNew, CellStrNew, CellColNew)
    {
        hexagon.setFillColor(sf::Color(207, 66, 52)); // Красный
        medicine = rand() % 12;
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
    }
    void Update(Map& map)
    {}
    ~Poison() override = default;
};

#endif //EVOLUTION_FOOD_HPP
