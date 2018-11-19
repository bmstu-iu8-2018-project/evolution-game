#ifndef EVOLUTION_FOOD_HPP
#define EVOLUTION_FOOD_HPP

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
        hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
        medicine = Medicine;
    }

    void Update(Map&) override
    {}

    ~Food() = default;

    void Print(sf::RenderWindow* window) override
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
        hexagon.setFillColor(sf::Color(66, 170, 255)); // Blue
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
        medicine = 0;
    }
    void Update(Map& map) override
    {}
    ~Water() = default;

    void Print(sf::RenderWindow* window) override
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
        hexagon.setFillColor(sf::Color(207, 66, 52)); // Red
        medicine = Medicine;
        hexagon.setOutlineThickness(1);
        hexagon.setOutlineColor(sf::Color::Black);
    }
    void Update(Map& map) override
    {}
    ~Poison() = default;

    void Print(sf::RenderWindow* window) override
    {
        sf::CircleShape hexagon1(10, 6);
        hexagon1.setFillColor(sf::Color(207, 66, 52));
        hexagon1.setOutlineThickness(1);
        hexagon1.setOutlineColor(sf::Color::Black);
        hexagon1.setPosition(x, y);
        window->draw(hexagon1);
    }
};

#endif //EVOLUTION_FOOD_HPP
