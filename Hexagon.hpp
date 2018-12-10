#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <atomic>
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
public:
    Hexagon() = default;

    virtual ~Hexagon() = default;

    Hexagon(const Type& type1, double xNew, double yNew, size_t CellStrNew, size_t CellColNew);
    Hexagon(const Type& type, const float xNew, const float yNew, const size_t CellStrNew,
                 const size_t CellColNew, const double lifesNew);
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

    virtual void Print(sf::RenderWindow*) const;

    bool IsAlive();

    virtual void SaveToFile(const std::string&) const;
protected:
    double x;  // координата по х как номер ячейки
    double y;  // координата по у как номер ячейки
    size_t cellStr;
    size_t cellCol;
    Type type;
    double lifes;
    double medicine;  // отрицательна если яд и положительна если лекарство
    bool isHealfy = true;
    int intrand(int a, int b)
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> dis(a, b);
        return dis(e);
    }
};


#endif
