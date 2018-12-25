#ifndef EVOLUTION_BUTTON_HPP_
#define EVOLUTION_BUTTON_HPP_

#include <cmath>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


/// @brief Класс кнопки
class Button
{
public:
    /// @brief Конструктор по умочанию
    Button() = default;
    /// @brief Деструктор по умолчанию
    ~Button() = default;
    /// @brief Конструктор, создающий кнопку с заданными координатами и поворотом
    /// @param x расположения кнопки в пикселях по оси Ox на окне
    /// @param y расположения кнопки в пикселях по оси Oy на окне
    /// @param rotation угол поворота
    Button(const float x, const float y, const float rotation);
    /// @brief Функция для получения координаты кнопки по оси Ox
    /// @return координаты кнопки по оси Ox
    double GetX();
    /// @brief Функция для получения координаты кнопки по оси Oy
    /// @return координаты кнопки по оси Oy
    double GetY();
    /// @brief Функция для получения цвета кнопки
    /// @return цвет кнопки
    sf::Color GetColor();
    /// @brief Функция для получения кнопки-треугольника
    /// @return кнопка-треугольник
    sf::CircleShape GetButton();
    /// @brief Функция для получения цвета кнопки
    /// @return цвет кнопки
    void SetColor(sf::Color newColor);
    /// @brief Функция для получения цвета кнопки
    /// @return цвет кнопки
    void SetX(double newX);
    /// @brief Функция для получения цвета кнопки
    /// @return цвет кнопки
    void SetY(double newY);
    /// @brief Функция для получения цвета кнопки
    /// @return цвет кнопки
    void Print(sf::RenderWindow* window);

private:
    /// @brief Форма кнопки
    sf::CircleShape button;
    /// @brief расположение кнопки в пикселях по оси Ox на окне
    float X;
    /// @brief расположение кнопки в пикселях по оси Oy на окне
    float Y;
    /// @brief Цвет кнопки
    sf::Color Color;
    /// @brief Угол поворота кнопки
    float Rotation;
};


#endif //  EVOLUTION_BUTTON_HPP_
