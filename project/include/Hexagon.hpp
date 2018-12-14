#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <random>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Brain.hpp"

class Map;

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
    Hexagon() = default;

    virtual ~Hexagon() = default;

    Hexagon(const Type, double, double, size_t, size_t);
    Hexagon& operator=(const Hexagon*);

    double GetX() const;
    double GetY() const;
    size_t GetCellStr() const;
    size_t  GetCellCol() const;
    Type GetType() const;
    double GetLifes() const;
    double GetMedicine() const;
    bool GetisHealfy() const;

    void SetX(double);
    void SetY(double);
    void SetCellStr(size_t);
    void SetCellCol(size_t);
    void SetType(Type&);
    void SetLifes(double);
    void SetMedicine(double);
    void ResetMedicine();

    bool IsAlive();

    virtual void Print(sf::RenderWindow*) const;
protected:
    double x;  // координата по х(в пикселях) как номер ячейки
    double y;  // координата по у(в пикселях) как номер ячейки
    size_t cellStr;
    size_t cellCol;
    Type type;
    double lifes;
    double medicine;  // отрицательна если яд и положительна если лекарство
    bool isHealfy = true;
};


#endif
