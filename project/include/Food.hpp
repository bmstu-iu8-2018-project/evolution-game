#ifndef EVOLUTION_FOOD_HPP_
#define EVOLUTION_FOOD_HPP_

#include "Hexagon.hpp"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

/// @brief Класс Еды
class Food
        : public Hexagon
{
public:
    /// @brief Конструктор, создающий гекс-еды с заданными координатами
    /// @param xNew расположение гекса-еды в пикселях по оси Ox на окне
    /// @param yNew расположение гекса-еды в пикселях по оси Oy на окне
    /// @param CellStrNew номер строки в матрице карты
    /// @param CellColNew номер столбца в матрице карты
    /// @param Medicine степнь ядовитости еды
    Food(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, double Medicine = rand() % 5)
        :    Hexagon(Type::FOOD, xNew, yNew, CellStrNew, CellColNew)
    {
        medicine = Medicine;
    }
    /// @brief Деструктор по умолчанию
    ~Food() override = default;
    /// @brief Функция отрисовки гекса-еды
    /// @param window окно, в котором нужно отрисовать гекс-еду
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

/// @brief Класс Воды
class Water
        : public Hexagon
{
public:
    /// @brief Конструктор, создающий гекс-воды с заданными координатами
    /// @param xNew расположение гекса-воды в пикселях по оси Ox на окне
    /// @param yNew расположение гекса-воды в пикселях по оси Oy на окне
    /// @param CellStrNew номер строки в матрице карты
    /// @param CellColNew номер столбца в матрице карты
    Water(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
            :    Hexagon(Type::WATER, xNew, yNew, CellStrNew, CellColNew)
    {
        medicine = 0;
    }
    /// @brief Деструктор по умолчанию
    ~Water() override = default;
    /// @brief Функция отрисовки гекса-воды
    /// @param window окно, в котором нужно отрисовать гекс-воду
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

/// @brief Класс Яда
class Poison
        : public Hexagon
{
public:
    /// @brief Конструктор, создающий гекс-яд с заданными координатами
    /// @param xNew расположение гекса-яд в пикселях по оси Ox на окне
    /// @param yNew расположение гекса-яд в пикселях по оси Oy на окне
    /// @param CellStrNew номер строки в матрице карты
    /// @param CellColNew номер столбца в матрице карты
    /// @param Medicine степнь ядовитости яда
    Poison(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, double Medicine = -(rand() % 12))
            :    Hexagon(Type::POISON, xNew, yNew, CellStrNew, CellColNew)
    {
        medicine = Medicine;
    }
    /// @brief Деструктор по умолчанию
    ~Poison() override = default;
    /// @brief Функция отрисовки гекса-яда
    /// @param window окно, в котором нужно отрисовать гекс-яда
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

/// @brief Класс Стены
class Wall
        : public Hexagon
{
public:
    /// @brief Конструктор, создающий гекс-стену
    Wall()
            :    Hexagon(Type::WALL, 0, 0, 0, 0)
    {
        medicine = 0;
        lifes = 0;
    }
    /// @brief Деструктор по умолчанию
    ~Wall() override = default;
};

#endif  //  EVOLUTION_FOOD_HPP_
