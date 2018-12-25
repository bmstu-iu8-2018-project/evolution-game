#ifndef EVOLUTION_HEXAGON_HPP_
#define EVOLUTION_HEXAGON_HPP_

#include <random>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Brain.hpp"

class Map;


/// @brief Родительский класс, описывающий шестиугольник(гекс)

class Hexagon
{
public:

    enum Type : int
    {
        FOOD = 1,
        WATER,
        POISON,
        PIXEL,
        WALL
    };

    /// @brief Конструктор по умочанию
    Hexagon() = default;
    /// @brief Конструктор, создающий гекс определенного типа с заданными координатами
    /// @param Type определитель типа гекса(например, вода)
    /// @param xInPixels расположение гекса в пикселях по оси Ox на окне
    /// @param yInPixels расположение гекса в пикселях по оси Oy на окне
    /// @param xInCells номер строки в матрице карты
    /// @param yInCells номер столбца в матрице карты
    Hexagon(const Type, double xInPixels, double yInPixels, size_t xInCells, size_t yInCells);
    /// @brief Конструктор копирования
    /// @param hex указатель на гекс, который нужно скопировать
    Hexagon& operator=(const Hexagon* hex);
    /// @brief Деструктор по умолчанию
    virtual ~Hexagon() = default;
    /// @brief Функция для получения расположения гекса в пикселях по оси Ox на окне
    /// @return расположение гекса в пикселях по оси Ox на окне
    double GetX() const;
    /// @brief Функция для получения расположения гекса в пикселях по оси Oy на окне
    /// @return расположение гекса в пикселях по оси Oy на окне
    double GetY() const;
    /// @brief Функция для получения номера строки в матрице карты, на которой расположен гекс
    /// @return номер строки в матрице карты, на которой расположен гекс
    size_t GetCellStr() const;
    /// @brief Функция для получения номера столбца в матрице карты, на котором расположен гекс
    /// @return номер столбца в матрице карты, на котором расположен гекс
    size_t  GetCellCol() const;
    /// @brief Функция для получения типа гекс(например, вода)
    /// @return тип гекса(например, вода)
    Type GetType() const;
    /// @brief Функция для получения количества жизней гекса
    /// @return количество жизней гекса
    double GetLifes() const;
    /// @brief Функция для получения степени ядовитости гекса
    /// @return степень ядовитости гекса
    double GetMedicine() const;
    /// @brief Функция для получения состояния здоровья гекса
    /// @return состояние здоровья гекса
    bool GetisHealfy() const;
    /// @brief Функция для установки расположения гекса в пикселях по оси Ox на окне
    /// @param x расположение гекса в пикселях по оси Ox на окне
    void SetX(double x);
    /// @brief Функция для установки расположения гекса в пикселях по оси Oy на окне
    /// @param y расположение гекса в пикселях по оси Oy на окне
    void SetY(double y);
    /// @brief Функция для установки номера строки в матрице карты, на которой расположен гекс
    /// @param xInCells номер строки в матрице карты, на которой расположен гекс
    void SetCellStr(size_t xInCells);
    /// @brief Функция для установки номера столбца в матрице карты, на котором расположен гекс
    /// @param yInCells номер столбца в матрице карты, на котором расположен гекс
    void SetCellCol(size_t yInCells);
    /// @brief Функция для установки типа гекса(например, вода)
    /// @param t тип гекса(например, вода)
    void SetType(Type& t);
    /// @brief Функция для установки колочества жизней гекса
    /// @param l количество жизней гекса
    void SetLifes(double l);
    /// @brief Функция для установки степени ядовитости гекса
    /// @param m степень ядовитости гекса
    void SetMedicine(double m);
    /// @brief Функция для обнуления степения ядовитости гекса
    void ResetMedicine();
    /// @brief Функция для проверки жизнеспособности гекса
    /// @return true - в случае, если гекс жив, иначе false
    bool IsAlive();
    /// @brief Функция для отрисовки гекса
    /// @param window указатель на окно, в котором требуется отрисовать гекс
    virtual void Print(sf::RenderWindow* window) const;
protected:
    /// @brief расположение гекса в пикселях по оси Ox на окне
    double x;
    /// @brief расположения гекса в пикселях по оси Oy на окне
    double y;
    /// @brief номер строки в матрице карты, на которой расположен гекс
    size_t cellStr;
    /// @brief номер столбца в матрице карты, на котором расположен гекс
    size_t cellCol;
    /// @brief тип гекса(например, вода)
    Type type;
    /// @brief количество жизней гекса
    double lifes;
    /// @brief степень ядовитости гекса
    double medicine;
    /// @brief состояние здоровья гекса
    bool isHealfy = true;

};


#endif //  EVOLUTION_HEXAGON_HPP_
