#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <atomic>
#include <SFML/Graphics/CircleShape.hpp>
#include "Brain.hpp"
#include <boost/any.hpp>

class Map;

class Hexagon
{
public:

    enum Type : int
    {
        FOOD = 1,
        WATER,
        POISON,
        PIXEL
        //  SOIL
    };
    Brain brain;
public:
    Hexagon() = default;

    virtual ~Hexagon() = default;

    Hexagon(const Type& type1, double xNew, double yNew, size_t CellStrNew, size_t CellColNew);
    Hexagon(const Type& type, const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t CellStrNew,
                 const size_t CellColNew, const double lifesNew, Brain brainNew);
    Hexagon& operator=(const Hexagon& hex);

    void Swap(Hexagon& hex);
    //virtual void Update(Map& map);

    double GetX() const;
    double GetY() const;
    sf::CircleShape GetHex() const;
    size_t GetCellStr() const;
    size_t  GetCellCol() const;
    Type GetType() const;
    double GetLifes() const;
    double GetMedicine() const;

    double& SetX();
    double& SetY();
    sf::CircleShape& SetHex();
    size_t& SetCellStr();
    size_t&  SetCellCol();
    Type& SetType();
    double& SetLifes();
    double& SetMedicine();

    //  void Die();

protected:
    sf::CircleShape hexagon = sf::CircleShape(10, 6); // сам шестиугольник
    double x;  // координата по х как номер ячейки
    double y;  // координата по у как номер ячейки
    size_t cellStr;
    size_t cellCol;
    Type type;
    double lifes;
    double medicine;  // отрицательна если яд и положительна если лекарство
    bool isHealfy = true;
};


#endif
