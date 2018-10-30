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
    std::shared_ptr<Brain> brain;
public:
    Hexagon() = default;

    virtual ~Hexagon() = default;

    Hexagon(const Type& type1, double xNew, double yNew, size_t CellStrNew, size_t CellColNew);
    // Hexagon(const Hexagon& hex);
    Hexagon& operator=(const Hexagon& hex);

    void Swap(Hexagon& hex);

    double& GetX();
    double& GetY();

    sf::CircleShape& GetHex();

    size_t& GetCellStr();
    size_t&  GetCellCol();

    Type& GetType();
    double& GetLifes();
    double& GetMedicine();

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
