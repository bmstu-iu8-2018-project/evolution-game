#ifndef EVOLUTION_FOOD_HPP
#define EVOLUTION_FOOD_HPP

#include "Hexagon.hpp"
#include </home/mariasolovyova/CLionProjects/Evolution/tools/json/single_include/nlohmann/json.hpp>

using Json = nlohmann::json;

class Food
        : public Hexagon
{
public:
    Food(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, double Medicine = rand() % 5)
        :    Hexagon(Type::FOOD, xNew, yNew, CellStrNew, CellColNew)
    {
        hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
        medicine = Medicine;
    }
    void Update(Map&) override
    {}
    ~Food() = default;
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
    void Update(Map& map) override
    {}
    ~Water() = default;
};

class Poison
        : public Hexagon
{
public:
    Poison(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, double Medicine = -(rand() % 12))
            :    Hexagon(Type::POISON, xNew, yNew, CellStrNew, CellColNew)
    {
        hexagon.setFillColor(sf::Color(207, 66, 52)); // Red
        medicine = Medicine;
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
    }
    void Update(Map& map) override
    {}
    ~Poison() = default;
};

#endif //EVOLUTION_FOOD_HPP
