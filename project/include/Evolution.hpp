#ifndef EVOLUTION_HPP_
#define EVOLUTION_HPP_

#include <thread>

#include <SFML/Window.hpp>

#include "Keyboard.hpp"
#include "Map.hpp"
#include "Pixel.hpp"
#include "Button.hpp"


/// @mainpage
/// @brief Моделирование Эволюции
/// @version 0.1.0
/// @author Мария Соловьева и Анастасия Важенина

/// @brief Класс Эволюции
class Evolution
{
    /// @brief Карта, на которой живут организмы
    Map map;
    /// @brief Окно для отрисовки
    sf::RenderWindow window;
    /// @brief клавиатура
    Keyboard keyboard;
    /// @brief кнопка, ускоряющая скорость моделирования
    Button buttonIncrease;
    /// @brief кнопка, затормаживающая скорость моделирования
    Button buttonDecrease;
    /// @brief Переменная, отвечающая за отрисовку карты, если скорость моделирования слишком велика, не отрисовывать
    bool PrintOrNot;
public:
    /// @brief Конструктор по умочанию
    Evolution();
    /// @brief Деструктор по умолчанию
    ~Evolution() = default;
    /// @brief Функция запуска эволюции
    void run();
    /// @brief Функция сбора статистики
    void Statistics();
    /// @brief Функция, показа меню
    void Menu();
};

#endif  //  EVOLUTION_HPP_