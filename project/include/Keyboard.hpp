#ifndef EVOLUTION_KEYBOARD_HPP_
#define EVOLUTION_KEYBOARD_HPP_

#include <map>
#include <SFML/Graphics.hpp>

/// @brief Класс Клавиатуры
class Keyboard
{
    /// @brief Нажатые клавиши
    std::map<sf::Keyboard::Key, bool> keys;
public:
    /// @brief Функция добавления ключа нажатой кнопки
    /// @param ключ нажатой кнопки
    void press(sf::Keyboard::Key key);
    /// @brief Функция отжатия кнопки
    /// @param ключ отжатой кнопки
    void release(sf::Keyboard::Key key);
    /// @brief Функция проверки : Нажата ли кнопка?
    /// @param ключ нажатой кнопки
    /// @return true, если нажатаб false - иначе
    bool isPressed(sf::Keyboard::Key key);
};

#endif  //  EVOLUTION_KEYBOARD_HPP_
